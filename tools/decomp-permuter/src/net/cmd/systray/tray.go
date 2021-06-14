package main

import (
	"bufio"
	"encoding/base64"
	"encoding/json"
	"fmt"
	"os"
	"os/signal"
	"reflect"
	"strings"
	"syscall"

	"github.com/getlantern/systray"
)

func main() {
	systray.Run(onReady, onExit)
}

func onExit() {
	os.Exit(0)
}

// Item represents an item in the menu
type Item struct {
	Icon       string `json:"icon"`
	Title      string `json:"title"`
	Tooltip    string `json:"tooltip"`
	Enabled    bool   `json:"enabled"`
	Checked    bool   `json:"checked"`
	Hidden     bool   `json:"hidden"`
	Items      []Item `json:"items"`
	InternalID int    `json:"__id"`
}

// Menu has an icon, title and list of items
type Menu struct {
	Icon    string `json:"icon"`
	Title   string `json:"title"`
	Tooltip string `json:"tooltip"`
	Items   []Item `json:"items"`
}

// Action for an item?..
type Action struct {
	Type  string `json:"type"`
	Item  Item   `json:"item"`
	Menu  Menu   `json:"menu"`
}

// ClickEvent for an click event
type ClickEvent struct {
	Type       string `json:"type"`
	InternalID int    `json:"__id"`
}

func readJSON(reader *bufio.Reader, v interface{}) error {
	input, err := reader.ReadString('\n')
	if err != nil {
		return err
	}
	if len(input) < 1 {
		return fmt.Errorf("Empty line")
	}

	lineReader := strings.NewReader(input[0 : len(input)-1])
	if err := json.NewDecoder(lineReader).Decode(v); err != nil {
		return err
	}

	return nil
}

func addMenuItem(items *[]*systray.MenuItem, seqID2InternalID *[]int, internalID2SeqID *map[int]int, item *Item, parent *systray.MenuItem) {
	if item.Title == "<SEPARATOR>" {
		systray.AddSeparator()
		*items = append(*items, nil)
	} else {
		var menuItem *systray.MenuItem
		if parent == nil {
			menuItem = systray.AddMenuItem(item.Title, item.Tooltip)
		} else {
			menuItem = parent.AddSubMenuItem(item.Title, item.Tooltip)
		}
		if item.Checked {
			menuItem.Check()
		} else {
			menuItem.Uncheck()
		}
		if item.Enabled {
			menuItem.Enable()
		} else {
			menuItem.Disable()
		}
		if len(item.Icon) > 0 {
			icon, err := base64.StdEncoding.DecodeString(item.Icon)
			if err != nil {
				fmt.Fprintln(os.Stderr, err)
			} else {
				menuItem.SetIcon(icon)
			}
		}
		for i := 0; i < len(item.Items); i++ {
			subitem := item.Items[i]
			addMenuItem(items, seqID2InternalID, internalID2SeqID, &subitem, menuItem)
		}
		if item.Hidden {
			menuItem.Hide()
		}
		*items = append(*items, menuItem)
	}
	seqID := len(*items) - 1
	(*internalID2SeqID)[item.InternalID] = seqID
	*seqID2InternalID = append(*seqID2InternalID, item.InternalID)
}

func onReady() {
	signalChannel := make(chan os.Signal, 2)
	signal.Notify(signalChannel, os.Interrupt, syscall.SIGTERM)
	go func() {
		for sig := range signalChannel {
			switch sig {
			case os.Interrupt, syscall.SIGTERM:
				// handle SIGINT, SIGTERM
				fmt.Fprintln(os.Stderr, "Quit")
				systray.Quit()
			default:
				fmt.Fprintln(os.Stderr, "Unhandled signal:", sig)
			}
		}
	}()

	items := make([]*systray.MenuItem, 0)
	seqID2InternalID := make([]int, 0)
	internalID2SeqID := make(map[int]int)
	fmt.Println(`{"type": "ready"}`)
	reader := bufio.NewReader(os.Stdin)

	var menu Menu
	if err := readJSON(reader, &menu); err != nil {
		fmt.Fprintln(os.Stderr, err)
		systray.Quit()
		return
	}

	icon, err := base64.StdEncoding.DecodeString(menu.Icon)
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		systray.Quit()
		return
	}

	systray.SetIcon(icon)
	systray.SetTitle(menu.Title)
	systray.SetTooltip(menu.Tooltip)

	updateItem := func(action Action) {
		item := action.Item
		seqID := internalID2SeqID[action.Item.InternalID]
		menuItem := items[seqID]
		if menuItem == nil {
			return
		}
		if item.Hidden {
			menuItem.Hide()
		} else {
			if item.Checked {
				menuItem.Check()
			} else {
				menuItem.Uncheck()
			}
			if item.Enabled {
				menuItem.Enable()
			} else {
				menuItem.Disable()
			}
			menuItem.SetTitle(item.Title)
			menuItem.SetTooltip(item.Tooltip)
			if len(item.Icon) > 0 {
				icon, err := base64.StdEncoding.DecodeString(item.Icon)
				if err != nil {
					fmt.Fprintln(os.Stderr, err)
				} else {
					menuItem.SetIcon(icon)
				}
			}
			menuItem.Show()
			for _, child := range item.Items {
				seqID = internalID2SeqID[child.InternalID]
				items[seqID].Show()
			}
		}
	}

	updateMenu := func(action Action) {
		m := action.Menu
		if menu.Title != m.Title {
			menu.Title = m.Title
			systray.SetTitle(menu.Title)
		}
		if menu.Icon != m.Icon && m.Icon != "" {
			menu.Icon = m.Icon
			icon, err := base64.StdEncoding.DecodeString(menu.Icon)
			if err != nil {
				fmt.Fprintln(os.Stderr, err)
			} else {
				systray.SetIcon(icon)
			}
		}
		if menu.Tooltip != m.Tooltip {
			menu.Tooltip = m.Tooltip
			systray.SetTooltip(menu.Tooltip)
		}
	}

	update := func(action Action) {
		switch action.Type {
		case "update-item":
			updateItem(action)
		case "update-menu":
			updateMenu(action)
		case "update-item-and-menu":
			updateItem(action)
			updateMenu(action)
		case "exit":
			systray.Quit()
		}
	}

	for i := 0; i < len(menu.Items); i++ {
		item := menu.Items[i]
		addMenuItem(&items, &seqID2InternalID, &internalID2SeqID, &item, nil)
	}

	go func(reader *bufio.Reader) {
		for {
			var action Action
			if err := readJSON(reader, &action); err != nil {
				fmt.Fprintln(os.Stderr, err)
				systray.Quit()
				break
			}
			update(action)
		}
	}(reader)

	stdoutEnc := json.NewEncoder(os.Stdout)
	for {
		itemsCnt := 0
		for _, ch := range items {
			if ch != nil {
				itemsCnt++
			}
		}
		cases := make([]reflect.SelectCase, itemsCnt)
		caseCnt2SeqID := make([]int, len(items))
		itemsCnt = 0
		for i, ch := range items {
			if ch == nil {
				continue
			}
			cases[itemsCnt] = reflect.SelectCase{Dir: reflect.SelectRecv, Chan: reflect.ValueOf(ch.ClickedCh)}
			caseCnt2SeqID[itemsCnt] = i
			itemsCnt++
		}

		remaining := len(cases)
		for remaining > 0 {
			chosen, _, ok := reflect.Select(cases)
			if !ok {
				// The chosen channel has been closed, so zero out the channel to disable the case
				cases[chosen].Chan = reflect.ValueOf(nil)
				remaining--
				continue
			}
			seqID := caseCnt2SeqID[chosen]
			err := stdoutEnc.Encode(ClickEvent{
				Type:       "clicked",
				InternalID: seqID2InternalID[seqID],
			})
			if err != nil {
				fmt.Fprintln(os.Stderr, err)
			}
		}
	}
}
