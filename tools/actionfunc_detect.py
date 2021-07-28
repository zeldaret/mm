#!/usr/bin/env python3

import enum
import os

def rename_function(global_asm_path, old, new):
    # Change functions.txt
    funcs = ""
    with open("tools/disasm/functions.txt", "r") as infile:
        funcs = infile.read()
    
    funcs = funcs.replace(old, new)

    with open("tools/disasm/functions.txt", "w") as outfile:
        outfile.write(funcs)

    # Change GLOBAL_ASM file
    asm = ""
    with open(global_asm_path, "r") as infile:
        asm = infile.read()
    
    asm = asm.replace(old, new)

    with open(global_asm_path, "w") as outfile:
        outfile.write(asm)
    
    # Rename GLOBAL_ASM file
    os.rename(global_asm_path, global_asm_path.replace(old, new))


for root, dirs, files in os.walk("src/overlays/actors/"):
    for actor_c_file in [f for f in files if f.endswith(".c")]:
        # Skip player
        if "z_player" in actor_c_file:
            continue

        c_src = ""
        with open(os.path.join(root,actor_c_file), "r") as infile:
            c_src = infile.read()

        # already done or worked on
        if "#pragma GLOBAL_ASM(" not in c_src or "_Init.s\")" not in c_src or "#ifdef NON_MATCHING" in c_src:
            continue

        actor_h_file = os.path.join(root, actor_c_file.replace(".c", ".h"))
        ovl_name = root.split(os.path.sep)[-1]
        actor_name = ovl_name.replace("ovl_","").replace("_","")
        actor_asm = f"asm/non_matchings/overlays/{ovl_name}/"

        is_dynapoly_actor = False
        action_func_offset = -1
        setup_action_func = None
        action_funcs = set()

        #   Entrypoint Analysis

        for asm_root, asm_dirs, asm_files in os.walk(actor_asm):
            for asm_file in asm_files:
                asm = ""
                with open(os.path.join(asm_root,asm_file), "r") as _asm_file:
                    asm = _asm_file.read()

                if asm_file.endswith("_Init.s"): # Init Function
                    # Dynapoly Actor check
                    if "BcCheck3_BgActorInit" in asm:
                        is_dynapoly_actor = True
                elif asm_file.endswith("_Update.s"): # Update Function
                    reg = None
                    for line in reversed(asm.split("\n")):
                        if not "glabel L80" in line and "glabel " in line:
                            break
                        if "jalr" in line:
                            reg = line.split("jalr")[1].strip()
                        elif "lw" in line and f"{reg}, " in line and "%lo" not in line:
                            action_func_offset = line.split(", ")[1].strip().split("(")[0].strip()
                            action_func_offset = int(action_func_offset, 16 if action_func_offset.startswith("0x") else 10)
                            # print("ActionFunc at " + hex(action_func_offset))
                            # print(f"typedef void (*{actor_name}ActionFunc)(struct {actor_name}* this, GlobalContext* globalCtx);")
                            break
                        elif "jal " in line and reg != None:
                            break

        #   Actor has no action function, no reason to do anything else here

        if action_func_offset == -1:
            # print("No actionfunc")
            continue

        #   Find the SetupAction function, if the actor has one

        for asm_root, asm_dirs, asm_files in os.walk(actor_asm):
            for asm_file in asm_files:
                asm = ""
                with open(os.path.join(asm_root,asm_file), "r") as _asm_file:
                    asm = _asm_file.read()

                if ".text" in asm:
                    asm = asm.split(".text\n")[1]

                started = False
                found = [False, False, False]
                for line in asm.split("\n"):
                    if "glabel " in line:
                        started = True
                        continue
                    if started:
                        if f"sw" in line and f"$a1, 0x{action_func_offset:x}($a0)" in line:
                            found[0] = True
                        elif found[0] and "jr" in line and "$ra" in line:
                            found[1] = True
                        elif found[1] and "nop" in line:
                            found[2] = True
                        else:
                            break
                    if all(found):
                        setup_action_func = asm_file.replace(".s","")
                        # print("Found SetupAction func")
                        # print(f"{setup_action_func} is {actor_name}_SetupAction({actor_name}* this, {actor_name}ActionFunc actionFunc);")

        #   Find action functions, we know what type they should be

        for asm_root, asm_dirs, asm_files in os.walk(actor_asm):
            for asm_file in asm_files:
                asm = ""
                with open(os.path.join(asm_root,asm_file), "r") as _asm_file:
                    asm = _asm_file.read()

                reversed_asm_lines = list(reversed(asm.split("\n")))

                reg = None
                setup_call_found = False
                for i,line in enumerate(reversed_asm_lines,0):
                    if ".text" in line:
                        break
                    if "glabel " in line:
                        continue
                    if "sw" in line and f", 0x{action_func_offset:X}(" in line:
                        reg = line.split("sw ")[1].strip().split(",")[0].strip()
                    elif "addiu" in line and f"{reg}, " in line and "%lo" in line:
                        action_funcs.add(line.split("%lo(")[1].strip().split(")")[0].strip())
                    elif setup_call_found and "addiu" in line and "$a1, " in line and "%lo" in line:
                        action_funcs.add(line.split("%lo(")[1].strip().split(")")[0].strip())
                    elif "jal" in line and setup_action_func is not None and f"{setup_action_func}" in line:
                        delayed_line = reversed_asm_lines[i + 1]
                        if "addiu" in delayed_line and "$a1, " in delayed_line and "%lo" in delayed_line:
                            action_funcs.add(delayed_line.split("%lo(")[1].strip().split(")")[0].strip())
                        else:
                            setup_call_found = True
                    elif "jal " in line:
                        if reg != None:
                            reg = None
                        if setup_call_found:
                            setup_call_found = False
                    elif "lui" in line and "$a1, " in line and setup_call_found:
                        setup_call_found = False
                    elif "lui" in line and f"{reg}, " in line:
                        reg = None

        #   Sort action functions by vaddr

        action_funcs = list(sorted(set(action_funcs), key=lambda x: int(x[5:], 16)))

        #   Add actionfunc to header & struct

        print(actor_name)

        h_src = ""
        with open(actor_h_file, "r") as infile:
            h_src = infile.read()

        def member_offset(member):
            return int(member.strip().split("/* ")[1].split(" */")[0], 16)

        struct_body = "    " + h_src.split(" {")[1].split("} ")[0].strip()
        struct_size = int(h_src.split("// size = ")[1].split("\n")[0].strip(), 16)

        struct_members = struct_body.split("\n")
        member_sizes = []

        for i,member in enumerate(struct_members,0):
            this_offset = member_offset(member)
            next_offset = member_offset(struct_members[i + 1]) if i < len(struct_members) - 1 else struct_size
            
            member_sizes.append(next_offset - this_offset)

        member_offsets = [member_offset(member) for member in struct_members]
        member_types = [member.split("*/ ")[1].split(" ")[0] for member in struct_members]
        member_names = [member.split("*/ ")[1].split(" ")[1].split(";")[0] for member in struct_members]

        # (offset, name, type, size)
        struct_members = list(zip(member_offsets,member_names,member_types,member_sizes))

        def fix_name(name, offset, size):
            new_name = name
            if "[" in new_name: # correct array size
                new_name = new_name.split("[")[0] + f"[0x{size:X}]"
            if "unk" in new_name: # correct unk name
                if "[" in new_name:
                    new_name = f"unk_{offset:X}[" + new_name.split("[")[1]
                else:
                    new_name = f"unk_{offset:X}"

            return new_name

        found = False
        new_members = []
        for member in struct_members:
            if not found and member[0] <= action_func_offset and member[0] + member[3] > action_func_offset:
                assert member[2] == 'char'
                assert action_func_offset - member[0] + 4 <= member[3]

                # actionfunc is in this member

                member_actionfunc_offset = action_func_offset - member[0]
                if member_actionfunc_offset == 0:
                    # at the start
                    new_members.extend([
                        (member[0], "actionFunc", f"{actor_name}ActionFunc", 4),
                        (member[0] + 4, fix_name(member[1], member[0], member[3] - 4), member[2], member[3] - 4),
                    ])
                elif member_actionfunc_offset + 4 == member[3]:
                    # at the end
                    new_members.extend([
                        (member[0], fix_name(member[1], member[0], member[3] - 4), member[2], member[3] - 4),
                        (member[0] + member_actionfunc_offset, "actionFunc", f"{actor_name}ActionFunc", 4),
                    ])
                else:
                    # in the middle
                    new_members.extend([
                        (member[0], fix_name(member[1], member[0], member_actionfunc_offset), member[2], member_actionfunc_offset),
                        (member[0] + member_actionfunc_offset, "actionFunc", f"{actor_name}ActionFunc", 4),
                        (member[0] + member_actionfunc_offset + 4, fix_name(member[1], member[0] + member_actionfunc_offset + 4, member[3] - member_actionfunc_offset - 4), member[2], member[3] - member_actionfunc_offset - 4),
                    ])
                found = True
            else:
                new_members.append(member)

        new_struct = ""
        for member in new_members:
            new_struct += f"    /* 0x{member[0]:04X} */ {member[2]} {member[1]};\n"
        new_struct = "    " + new_struct.strip()

        h_src = h_src.replace(f"struct {actor_name};", f"struct {actor_name};\n\ntypedef void (*{actor_name}ActionFunc)(struct {actor_name}* this, GlobalContext* globalCtx);")
        h_src = h_src.replace(struct_body, new_struct)

        print(h_src)
        #   with open(actor_h_file, "w") as outfile:
        #       outfile.write(h_src)

        # Add SetupAction and actionfunc prototypes to C source

        setup_action_prototype = ""
        if setup_action_func is not None:
            setup_action_prototype = f"\n\nvoid {actor_name}_SetupAction({actor_name}* this, {actor_name}ActionFunc actionFunc);"
            c_src = c_src.replace(setup_action_func + ".s", f"{actor_name}_SetupAction.s")

        actionfunc_prototypes = "\n".join([f"void {func}({actor_name}* this, GlobalContext* globalCtx);" for func in action_funcs])

        c_src = c_src.replace("#if 0", actionfunc_prototypes + setup_action_prototype + "\n\n#if 0")

        print(c_src)
        #   with open(os.path.join(root,actor_c_file), "w") as outfile:
        #       outfile.write(c_src)
