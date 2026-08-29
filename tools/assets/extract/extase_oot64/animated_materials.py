# SPDX-FileCopyrightText: © 2025 ZeldaRET
# SPDX-License-Identifier: CC0-1.0

from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from ..extase.memorymap import MemoryContext

from ..extase import (
    BinaryBlobResource,
)
from ..extase.cdata_resources import (
    CDataArrayResource,
    CDataExt_Struct,
    CDataExt_Value,
    CDataExtWriteContext,
)

Z64HDRPRFX = "z64"


class AnimatedMaterialResource(CDataArrayResource):
    def report_params(resource, memory_context: "MemoryContext", v):
        assert isinstance(v, int)
        address = v
        if address == 0:
            return
        try:
            memory_context.report_resource_at_segmented(
                resource,
                address,
                BinaryBlobResource,
                lambda file, offset: BinaryBlobResource(
                    file,
                    offset,
                    offset + 4,
                    f"{resource.name}_{offset:08X}_AnimatedMaterialParams",
                ),
            )
        except Exception as e:
            # FIXME ignoring exceptions for now,
            # it seems that "void* params" is not always a pointer?
            print(e)

    def write_params(
        resource, memory_context: "MemoryContext", v, wctx: CDataExtWriteContext
    ):
        assert isinstance(v, int)
        address = v
        if address == 0:
            wctx.f.write("NULL")
        else:
            wctx.f.write(memory_context.get_c_reference_at_segmented(address))
        return True

    elem_cdata_ext = CDataExt_Struct(
        (
            ("segment", CDataExt_Value.s8),
            ("pad1", CDataExt_Value.pad8),
            ("type", CDataExt_Value.s16),
            (
                "params",
                CDataExt_Value("I").set_report(report_params).set_write(write_params),
            ),
        )
    )

    def try_parse_data(self, memory_context):
        length = None

        if self.symbol_name in {
            "gEffPoppedDekuBubbleTexAnim",
            "gBusinessScrubEmptyTexAnim",
            "gTwinmoldEmpty1TexAnim",
            "gTwinmoldEmpty2TexAnim",
            "gSkullKidEmptyTexAnim",
            "gGaroEmpty1TexAnim",
            "gGaroEmpty2TexAnim",
            "gBeaverYoungerBrotherEmptyTexAnim",
            "gBurlyGuyEmpty1TexAnim",
            "gBurlyGuyEmpty2TexAnim",
            "gEyegoreEmpty1TexAnim",
            "gEyegoreEmpty2TexAnim",
            "gEyegoreEmpty3TexAnim",
            "gWoodfallSceneryPurifiedWallsTexAnim",
            "gWoodfallSceneryTempleTexAnim",
            "object_um_Matanimheader_007D10",
            "object_fall2_Matanimheader_005CF0",
            "gTurtleEmpty1TexAnim",
            "gTurtleEmpty2TexAnim",
            "object_iknv_obj_Matanimheader_0113E0",
            "object_botihasira_Matanimheader_001A48",
            "gGyorgEmpty1TexAnim",
            "gGyorgEmpty2TexAnim",
            "object_mnk_Matanimheader_019A20",
            "gAlienEmptyTexAnim",
            "gWizrobePlatformEmptyTexAnim",
            "gDmZl4EmptyTexAnim",
        }:
            # TODO investigate
            # this data uses segment=0 which should mean "keep going" per the code
            # but it doesn't really have a terminator beyond that
            length = 1

        if length is None:
            length = 1
            assert self.file.data is not None
            while True:
                v = self.elem_cdata_ext.unpack_from(
                    self.file.data,
                    self.range_start + (length - 1) * self.elem_cdata_ext.size,
                )
                if v["segment"] < 0:
                    break
                length += 1
        self.set_length(length)
        return super().try_parse_data(memory_context)

    def get_c_declaration_base(self):
        if hasattr(self, "HACK_IS_STATIC_ON"):
            return f"AnimatedMaterial {self.symbol_name}[{self._length}]"
        return f"AnimatedMaterial {self.symbol_name}[]"

    def get_h_includes(self):
        return ("ultra64.h", Z64HDRPRFX + "scene.h")
