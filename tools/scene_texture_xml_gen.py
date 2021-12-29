#!/usr/bin/env python3

import argparse, re
from typing import List

import shlex
from subprocess import Popen, PIPE
from pathlib import Path

SEGMENTED_TEXTURE_06 = re.compile(r"gsDPLoadTextureBlock\((?P<pointer>0x06[0-9A-Fa-f]{6}), (?P<fmt>[^,]+), (?P<size>[^,]+), (?P<width>[^,]+), (?P<height>[^,]+)")

TEXTURES_FORMATS = {
    "G_IM_FMT_CI": {
        "G_IM_SIZ_8b": "ci8",
    },
    "G_IM_FMT_I": {
        "G_IM_SIZ_8b": "i8",
    },
    "G_IM_FMT_RGBA": {
        "G_IM_SIZ_16b": "rgba16",
    },
}

def getScenePaths(sceneTextureId: int) -> List[Path]:
    cmd = f"grep -r 'SCENE_CMD_SKYBOX_SETTINGS(0x0{sceneTextureId}' assets/"
    process = Popen(shlex.split(cmd), stdout=PIPE)
    (output, err) = process.communicate()
    exit_code = process.wait()

    assert exit_code == 0

    pathList = []
    for line in output.decode("utf-8").splitlines():
        p = Path(line.split(":")[0])
        pathList.append(p.parent)

    return pathList

def getTexturesFromScenes(pathList: List[Path]) -> dict:
    texturesPerOffset = dict()

    for p in pathList:
        for filePath in p.iterdir():
            if filePath.suffix != ".c":
                continue

            with open(filePath) as f:
                for line in f:
                    result = SEGMENTED_TEXTURE_06.search(line)
                    if result is not None:
                        offset = int(result["pointer"], 16) & 0xFFFFFF
                        fmt = result["fmt"]
                        size = result["size"]
                        width = int(result["width"])
                        height = int(result["height"])

                        texFmt = TEXTURES_FORMATS[fmt][size]
                        texturesPerOffset[offset] = (texFmt, width, height)

    return texturesPerOffset

def printXml(sceneTextureId: int, texturesPerOffset: dict):
    print(f'<Root>')
    print(f'    <File Name="scene_texture_{sceneTextureId}" Segment="6">')

    sortedTextures = sorted(texturesPerOffset.items())
    for offset, (texFmt, width, height) in sortedTextures:
        print(f'        <Texture Name="scene_texture_{sceneTextureId}_Tex_{offset:06X}" OutName="tex_{offset:06X}" Format="{texFmt}" Width="{width}" Height="{height}" Offset="0x{offset:X}"/>')

    print(f'    </File>')
    print(f'</Root>')

def main():
    parser = argparse.ArgumentParser(description="scene_texture XML creator")
    parser.add_argument("sceneTextureId", help="Selects which scene_texture number you want. 1 would select scene_texture_01", choices=list(range(1, 8+1)), type=int)
    args = parser.parse_args()


    pathList = getScenePaths(args.sceneTextureId)
    texturesPerOffset = getTexturesFromScenes(pathList)
    printXml(args.sceneTextureId, texturesPerOffset)

if __name__ == "__main__":
    main()
