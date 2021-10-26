def apply(config, args):
    config["baseimg"] = "target.bin"
    config["myimg"] = "source.bin"
    config["mapfile"] = "build.map"
    config["source_directories"] = ["."]
    # config["show_line_numbers_default"] = True
    # config["arch"] = "mips"
    # config["map_format"] = "gnu" # gnu or mw
    # config["mw_build_dir"] = "build/" # only needed for mw map format
    # config["makeflags"] = []
    # config["objdump_executable"] = ""
