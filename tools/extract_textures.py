#!/usr/bin/env python3
import struct;
from tkinter import *;
from tkinter.ttk import *
from PIL import Image, ImageTk, ImageDraw

import png;

#FILE_NAME = 'baserom/jpn_font_static'
FILE_NAME = 'decomp/object_boss03'

data = []
image_data = [];

try:
    with open(FILE_NAME, 'rb') as f:
        data = f.read()
except IOError:
    print('failed to read file ' + FILE_NAME)
    sys.exit(1)

#size = 0x80
height = 32
width = 32
pixel_width = 2
size = height*width*pixel_width
scale = 4

window = Tk()

window.title("MM Texture viewer")
window.geometry('500x500')

def load_file():
    print('load')
    update_image()

def read_i4_image(data, image_data):
    for i in range(0, len(data)):
        byte = data[i]
        color1 = ((byte >> 4) & 0xF) * 17
        color2 = (byte & 0xF) * 17
        image_data.append(color1)
        image_data.append(color1)
        image_data.append(color1)
        image_data.append(255)
        image_data.append(color2)
        image_data.append(color2)
        image_data.append(color2)
        image_data.append(255)

def read_i8_image(data, image_data):
    for i in range(0, len(data)):
        byte = data[i]
        image_data.append(byte)
        image_data.append(byte)
        image_data.append(byte)
        image_data.append(255)

def read_ia4_image(data, image_data):
    None

def read_ia8_image(data, image_data):
    None

def read_ia16_image(data, image_data):
    None

def read_rbg5a1_image(data, image_data):
    for i in range(0, len(data) // 2):
        byte1 = data[i*2]
        byte2 = data[i*2 + 1]
        red = (byte1 >> 3)*8
        green = (((byte1&0x7)<<2) | ((byte2>>6)&0x3))*8
        blue = ((byte2 >> 1) & 0x1F)*8
        alpha = (byte2&0x1)*0xFF
        image_data.append(red)
        image_data.append(green)
        image_data.append(blue)
        image_data.append(alpha)

def read_rbga32_image(data, image_data):
    for i in range(0, len(data)):
        byte = data[i]
        image_data.append(byte)

def read_ci4_image(data, image_data):
    None

def read_ci8_image(data, image_data):
    None

def update_image(*args):
    global image_label
    global image_data
    global data

    image_data = []

    texture_type = texture_type_combo.get()
    if texture_type == 'i4':
        read_i4_image(data, image_data)
    elif texture_type == 'i8':
        read_i8_image(data, image_data)
    elif texture_type == 'ia4':
        read_ia4_image(data, image_data)
    elif texture_type == 'ia8':
        read_ia8_image(data, image_data)
    elif texture_type == 'ia16':
        read_ia16_image(data, image_data)
    elif texture_type == 'rbg5a1':
        read_rbg5a1_image(data, image_data)
    elif texture_type == 'rbga32':
        read_rbga32_image(data, image_data)
    elif texture_type == 'ci4':
        read_ci4_image(data, image_data)
    elif texture_type == 'ci8':
        read_ci8_image(data, image_data)
    else:
        print('other type')

    offset = int(offset_spinbox.get())

    image = Image.frombytes("RGBA", (width, height), bytes(image_data[offset*4:])).resize((width*scale, height*scale))
    image_tk = ImageTk.PhotoImage(image=image)
    image_label.configure(image=image_tk)
    image_label.image = image_tk # prevent GC?



load_button = Button(window, text='Load File', command=load_file)
load_button.pack()

texture_type_combo = Combobox(window)
texture_type_combo['values'] = ('i4', 'i8', 'ia4', 'ia8', 'ia16', 'rbg5a1', 'rbga32', 'ci4', 'ci8')
texture_type_combo.current(5)
texture_type_combo.bind("<<ComboboxSelected>>", update_image)
texture_type_combo.pack()

# TODO textures should be able to only take a few discret values, find them
width_default = StringVar(window)
width_default.set("32")
width_spinbox = Spinbox(window, from_=1, to=48, textvariable=width_default, command=update_image)
width_spinbox.pack();

offset_default = StringVar(window)
offset_default.set("0")
offset_spinbox = Spinbox(window, from_=0, to=len(data), textvariable=offset_default, command=update_image)
offset_spinbox.pack();

image_label = Label(window)
image_label.pack()

update_image()

window.mainloop()

#for i in range(0, len(data) // size):
#    texture_data = data[(i * size):((i + 1) * size)]
#
#    with open('font_test2/' + str(i) + '.png', 'wb') as f:
#        w = png.Writer(width, height, alpha=True)#, greyscale=True)#
#        png_data = [];
#        for y in range(0, height):
#            row = []
#            '''
#            for x in range(0, 16//2):
#                byte = texture_data[8*y + x]
#                row.append(((byte >> 4) & 0xF) * 17)
#                row.append((byte & 0xF) * 17)
#                '''
#            '''
#            for x in range(0, width*pixel_width):
#                byte = texture_data[width*pixel_width*y + x]
#                row.append(byte)
#                '''
#            png_data.append(row)
#        w.write(f, png_data)