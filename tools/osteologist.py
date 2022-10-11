#!/usr/bin/env python3
import argparse
import dataclasses
import struct
import sys
import typing

@dataclasses.dataclass
class StandardLimb:
    jointPosX: int
    jointPosY: int
    jointPosZ: int
    child: int
    sibling: int
    dList: int

    def __str__(self) -> str:
        return f"({self.jointPosX:5},{self.jointPosY:5},{self.jointPosZ:5}),   {self.child:2},     {self.sibling:2}, 0x{self.dList:08X}"

@dataclasses.dataclass
class LODLimb:
    jointPosX: int
    jointPosY: int
    jointPosZ: int
    child: int
    sibling: int
    dListNear: int
    dListFar: int

    def __str__(self) -> str:
        return f"({self.jointPosX:5},{self.jointPosY:5},{self.jointPosZ:5}),   {self.child:2},     {self.sibling:2}, 0x{self.dListNear:08X}, 0x{self.dListFar:08X}"

@dataclasses.dataclass
class CurveLimb:
    child: int
    sibling: int
    dList0: int
    dList1: int

    def __str__(self) -> str:
        return f"{self.child:2},{self.sibling:2}, 0x{self.dList0:08X}, 0x{self.dList1:08X}"

@dataclasses.dataclass
class SkinLimb:
    jointPosX: int
    jointPosY: int
    jointPosZ: int
    child: int
    sibling: int
    segmentType: int
    segment: int

    def __str__(self) -> str:
        return f"({self.jointPosX:5},{self.jointPosY:5},{self.jointPosZ:5}),   {self.child:2},     {self.sibling:2}, {self.segmentType:2}, 0x{self.segment:08X}"

@dataclasses.dataclass
class SkeletonHeader:
    limbTableOffset: int
    count: int

@dataclasses.dataclass
class FlexSkeletonHeader:
    limbTableOffset: int
    count: int
    dListCount: int
    

@dataclasses.dataclass
class Skeleton:
    header: typing.Union[SkeletonHeader,FlexSkeletonHeader]
    limbTable: typing.List[int] = dataclasses.field(default_factory=list)
    # Pylance and mypy are too stupid to understand using a union for this, so use a generic type
    limbs: typing.List = dataclasses.field(default_factory=list)

@dataclasses.dataclass
class  LegacyLimb:
    dList: int
    transX: float
    transY: float
    transZ: float
    rotX: int
    rotY: int
    rotZ: int
    sibling: int
    child: int

    def __str__(self) -> str:
        return f"0x{self.dList:08X}, ({self.transX:12f}f,{self.transY:12f}f,{self.transZ:12f}f), ({self.rotX:5X},{self.rotY:5X},{self.rotZ:5X}),   {self.sibling:2},     {self.child:2}"


# does not correspond to a C struct in OoT
@dataclasses.dataclass
class LegacySkeleton:
    limbTableOffset: int
    limbAddressDict: typing.Dict[int,int]
    limbs: typing.List[LegacyLimb]
    count: int

limb_formats: typing.Dict[str, str] = {
    "standard": ">hhhbbI",
    "lod": ">hhhbbII",
    "curve": ">bbxxII",
    "skin": ">hhhbbII",
    "legacy": ">IfffhhhxxII",
}

def SegmentedToOffset(address: int) -> int:
    return address & 0xFFFFFF

tee  = "├─ "
vert = "│  "
ell  = "└─ "
empt = "   "

# print_full_limb = False
# print_tree = True
# print_annotation = False


# Pylance and mypy are too stupid to understand using a union for this, so use a generic type for limbs
def PrintLimb(limbs: typing.List, index: int, next_line: typing.List[str]) -> None:
    limb = limbs[index]

    if print_full_limb:
        print(f"{limb}  ", end="")
    
    if print_tree:
        print("".join(next_line), end="")
        print(index, end="")

        if print_annotation:
            if isinstance(limb, (StandardLimb,LegacyLimb)) and limb.dList != 0:
                print("*", end="")
            elif isinstance(limb, CurveLimb):
                print(f"{'*' if limb.dList0 != 0 else '_' }{'*' if limb.dList1 != 0 else '_' }", end="")
            elif isinstance(limb, LODLimb):
                print(f"{'*' if limb.dListNear != 0 else '_' }{'*' if limb.dListFar != 0 else '_' }", end="")

    if print_full_limb or print_tree:
        print("")

    for i,elt in enumerate(next_line):
        if elt == tee:
            next_line[i] = vert
        elif elt == ell:
            next_line[i] = empt

    if limb.child != -1:
        if limb.sibling != -1:
            next_line.append(tee)
        else:
            next_line.append(ell)
        PrintLimb(limbs, limb.child, next_line)
        next_line.pop()

    if limb.sibling != -1:
        PrintLimb(limbs, limb.sibling, next_line)


def MakeLegacySkeleton(data: bytes, offset: int) -> LegacySkeleton:
    skeleton: LegacySkeleton = LegacySkeleton(
        offset, 
        {
            0: -1,
        }, 
        [], 
        0
    )
    limbOffset: int
    count: int = 0
    while True:
        limbOffset = SegmentedToOffset(struct.unpack_from(">I", data, offset=offset + struct.calcsize(">I") * count)[0])
        if limbOffset == 0:
            break
        
        skeleton.limbAddressDict[limbOffset] = count
        count += 1
    
    skeleton.count = count

    for limbOffset in skeleton.limbAddressDict:
        if limbOffset == 0:
            continue
        limb = LegacyLimb(*struct.unpack_from(limb_formats["legacy"], data, offset=limbOffset))
        limb.child = skeleton.limbAddressDict[SegmentedToOffset(limb.child)]
        limb.sibling = skeleton.limbAddressDict[SegmentedToOffset(limb.sibling)]
        skeleton.limbs.append(limb)

    return skeleton


def main() -> None:
    description = "Examine a Zelda64 skeleton and print useful information about it."
    epilog = "By default will print the header information and limbtable offset, apply flags for other information."

    parser = argparse.ArgumentParser(description=description, epilog=epilog, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument("object", help="object file to read.")
    parser.add_argument("skel", help="offset of skeleton header")
    parser.add_argument("type", help="type", choices=["normal", "flex", "curve", "legacy"])
    parser.add_argument("limb_type", help="limb type", choices=["standard", "lod", "skin", "curve", "legacy"])
    parser.add_argument("-l", help="print table of limbs", action="store_true")
    parser.add_argument("-t", help="print limb tree structure", action="store_true")
    parser.add_argument("-a", help="annotate limb tree with, e.g. which limbs have displaylists", action="store_true")

    args = parser.parse_args()
    
    global print_full_limb
    global print_tree
    global print_annotation

    print_full_limb = args.l
    print_tree = args.t
    print_annotation = args.a

    limb_type = args.limb_type
    skelOffset = int(args.skel, 0)

    skeleton: typing.Union[Skeleton,LegacySkeleton]

    with open(args.object, "rb") as f:
        data = f.read()

    if args.type == "normal" or args.type == "curve": 
        # these are functionally identical even if this is not strictly correct
        limbTableOffset, count = struct.unpack_from(">IB", data, offset=skelOffset)
        limbTableOffset = SegmentedToOffset(limbTableOffset)
        skeleton = Skeleton(header = SkeletonHeader(limbTableOffset,count))

        for i in range(count):
            limbOffset = struct.unpack_from(">I", data, offset=skeleton.header.limbTableOffset + struct.calcsize(">I") * i)[0]
            skeleton.limbTable.append(SegmentedToOffset(limbOffset))

        print(f"{args.type.capitalize()} skeleton at offset {skelOffset:X}, {skeleton.header.count} {limb_type} limbs")

    elif args.type == "flex":
        limbTableOffset, count, dListCount = struct.unpack_from(">IBxxxB", data, offset=skelOffset)
        limbTableOffset = SegmentedToOffset(limbTableOffset)
        skeleton = Skeleton(header = FlexSkeletonHeader(limbTableOffset,count,dListCount))

        for i in range(count):
            limbOffset = struct.unpack_from(">I", data, offset=skeleton.header.limbTableOffset + struct.calcsize(">I") * i)[0]
            skeleton.limbTable.append(SegmentedToOffset(limbOffset))

        assert(isinstance(skeleton.header,FlexSkeletonHeader))
        # Pylance complains about skeleton.header.dListCount, but it hasn't got any brains so we can ignore it.
        print(f"Skeleton at offset {skelOffset:X}, type {args.type}, {skeleton.header.count} {limb_type} limbs, {skeleton.header.dListCount} displaylists")

    elif args.type == "legacy":
        limbTableOffset = skelOffset
        skeleton = MakeLegacySkeleton(data,limbTableOffset)
        print(f"{args.type.capitalize()} skeleton, {skeleton.count} {limb_type} limbs")
        print(f"limbTable offset: {skeleton.limbTableOffset:X}")
        PrintLimb(skeleton.limbs, 0, [])
        exit(0)

    else:
        print(f"Skeleton type {args.type} not currently supported", file=sys.stderr)
        exit(1)
    
    if limb_type == "standard":
        for limbOffset in skeleton.limbTable:
            skeleton.limbs.append(StandardLimb(*struct.unpack_from(limb_formats[limb_type], data, offset=limbOffset)))
    elif limb_type == "lod":
        for limbOffset in skeleton.limbTable:
            skeleton.limbs.append(LODLimb(*struct.unpack_from(limb_formats[limb_type], data, offset=limbOffset)))
    elif limb_type == "skin":
        for limbOffset in skeleton.limbTable:
            skeleton.limbs.append(SkinLimb(*struct.unpack_from(limb_formats[limb_type], data, offset=limbOffset)))
    elif limb_type == "curve":
        for limbOffset in skeleton.limbTable:
            skeleton.limbs.append(CurveLimb(*struct.unpack_from(limb_formats[limb_type], data, offset=limbOffset)))
    else:
        print(f"Limb type {limb_type} not currently supported", file=sys.stderr)
        exit(1)

    print(f"limbTable offset: {skeleton.header.limbTableOffset:X}")
    # print("jointPos,           child,sibling,dList,        tree")
    PrintLimb(skeleton.limbs, 0, [])



if __name__ == "__main__":
    main()
