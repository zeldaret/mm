# SPDX-FileCopyrightText: © 2025 ZeldaRET
# SPDX-License-Identifier: CC0-1.0

import enum
import struct
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from ..extase.memorymap import MemoryContext

from ..extase import (
    File,
    Resource,
    RESOURCE_PARSE_SUCCESS,
    ResourceParseInProgress,
    ResourceParseWaiting,
)
from ..extase.cdata_resources import (
    CDataArrayResource,
    CDataExt_Value,
    CDataExtWriteContext,
)

from .. import oot64_data

from . import scene_rooms_resources
from . import collision_resources
from . import room_shape_resources
from . import misc_resources

Z64HDRPRFX = "z64"


def _SHIFTR(v: int, s: int, w: int):
    assert isinstance(v, int)
    assert isinstance(s, int)
    assert isinstance(w, int)
    assert v >= 0
    assert s >= 0
    assert w >= 1
    return (v >> s) & ((1 << w) - 1)


VERBOSE_NOT_FULLY_PARSED_SCENECMD = True
VERBOSE_ALT_HEADERS_GUESS_LENGTH = True


class SceneCmdId(enum.Enum):
    # keep the SCENE_CMD_ID_ prefix for grepability
    SCENE_CMD_ID_SPAWN_LIST = 0
    SCENE_CMD_ID_ACTOR_LIST = enum.auto()
    SCENE_CMD_ID_ACTOR_CUTSCENE_CAM_LIST = enum.auto()
    SCENE_CMD_ID_COL_HEADER = enum.auto()
    SCENE_CMD_ID_ROOM_LIST = enum.auto()
    SCENE_CMD_ID_WIND_SETTINGS = enum.auto()
    SCENE_CMD_ID_ENTRANCE_LIST = enum.auto()
    SCENE_CMD_ID_SPECIAL_FILES = enum.auto()
    SCENE_CMD_ID_ROOM_BEHAVIOR = enum.auto()
    SCENE_CMD_ID_UNK_09 = enum.auto()
    SCENE_CMD_ID_ROOM_SHAPE = enum.auto()
    SCENE_CMD_ID_OBJECT_LIST = enum.auto()
    SCENE_CMD_ID_LIGHT_LIST = enum.auto()
    SCENE_CMD_ID_PATH_LIST = enum.auto()
    SCENE_CMD_ID_TRANSI_ACTOR_LIST = enum.auto()
    SCENE_CMD_ID_ENV_LIGHT_SETTINGS = enum.auto()
    SCENE_CMD_ID_TIME_SETTINGS = enum.auto()
    SCENE_CMD_ID_SKYBOX_SETTINGS = enum.auto()
    SCENE_CMD_ID_SKYBOX_DISABLES = enum.auto()
    SCENE_CMD_ID_EXIT_LIST = enum.auto()
    SCENE_CMD_ID_END = enum.auto()
    SCENE_CMD_ID_SOUND_SETTINGS = enum.auto()
    SCENE_CMD_ID_ECHO_SETTINGS = enum.auto()
    SCENE_CMD_ID_CUTSCENE_SCRIPT_LIST = enum.auto()
    SCENE_CMD_ID_ALTERNATE_HEADER_LIST = enum.auto()
    SCENE_CMD_ID_SET_REGION_VISITED = enum.auto()
    SCENE_CMD_ID_ANIMATED_MATERIAL_LIST = enum.auto()
    SCENE_CMD_ID_ACTOR_CUTSCENE_LIST = enum.auto()
    SCENE_CMD_ID_MAP_DATA = enum.auto()
    SCENE_CMD_ID_UNUSED_1D = enum.auto()
    SCENE_CMD_ID_MAP_DATA_CHESTS = enum.auto()


# FIXME these names are just copypasting the id name, not the actual names yet
scene_cmd_macro_name_by_cmd_id = {
    SceneCmdId.SCENE_CMD_ID_SPAWN_LIST: "SCENE_CMD_SPAWN_LIST",
    SceneCmdId.SCENE_CMD_ID_ACTOR_LIST: "SCENE_CMD_ACTOR_LIST",
    SceneCmdId.SCENE_CMD_ID_ACTOR_CUTSCENE_CAM_LIST: "SCENE_CMD_ACTOR_CUTSCENE_CAM_LIST",
    SceneCmdId.SCENE_CMD_ID_COL_HEADER: "SCENE_CMD_COL_HEADER",
    SceneCmdId.SCENE_CMD_ID_ROOM_LIST: "SCENE_CMD_ROOM_LIST",
    SceneCmdId.SCENE_CMD_ID_WIND_SETTINGS: "SCENE_CMD_WIND_SETTINGS",
    SceneCmdId.SCENE_CMD_ID_ENTRANCE_LIST: "SCENE_CMD_ENTRANCE_LIST",
    SceneCmdId.SCENE_CMD_ID_SPECIAL_FILES: "SCENE_CMD_SPECIAL_FILES",
    SceneCmdId.SCENE_CMD_ID_ROOM_BEHAVIOR: "SCENE_CMD_ROOM_BEHAVIOR",
    SceneCmdId.SCENE_CMD_ID_UNK_09: "SCENE_CMD_UNK_09",
    SceneCmdId.SCENE_CMD_ID_ROOM_SHAPE: "SCENE_CMD_ROOM_SHAPE",
    SceneCmdId.SCENE_CMD_ID_OBJECT_LIST: "SCENE_CMD_OBJECT_LIST",
    SceneCmdId.SCENE_CMD_ID_LIGHT_LIST: "SCENE_CMD_LIGHT_LIST",
    SceneCmdId.SCENE_CMD_ID_PATH_LIST: "SCENE_CMD_PATH_LIST",
    SceneCmdId.SCENE_CMD_ID_TRANSI_ACTOR_LIST: "SCENE_CMD_TRANSITION_ACTOR_LIST",
    SceneCmdId.SCENE_CMD_ID_ENV_LIGHT_SETTINGS: "SCENE_CMD_ENV_LIGHT_SETTINGS",
    SceneCmdId.SCENE_CMD_ID_TIME_SETTINGS: "SCENE_CMD_TIME_SETTINGS",
    SceneCmdId.SCENE_CMD_ID_SKYBOX_SETTINGS: "SCENE_CMD_SKYBOX_SETTINGS",
    SceneCmdId.SCENE_CMD_ID_SKYBOX_DISABLES: "SCENE_CMD_SKYBOX_DISABLES",
    SceneCmdId.SCENE_CMD_ID_EXIT_LIST: "SCENE_CMD_EXIT_LIST",
    SceneCmdId.SCENE_CMD_ID_END: "SCENE_CMD_END",
    SceneCmdId.SCENE_CMD_ID_SOUND_SETTINGS: "SCENE_CMD_SOUND_SETTINGS",
    SceneCmdId.SCENE_CMD_ID_ECHO_SETTINGS: "SCENE_CMD_ECHO_SETTINGS",
    SceneCmdId.SCENE_CMD_ID_CUTSCENE_SCRIPT_LIST: "SCENE_CMD_CUTSCENE_SCRIPT_LIST",
    SceneCmdId.SCENE_CMD_ID_ALTERNATE_HEADER_LIST: "SCENE_CMD_ALTERNATE_HEADER_LIST",
    SceneCmdId.SCENE_CMD_ID_SET_REGION_VISITED: "SCENE_CMD_SET_REGION_VISITED",
    SceneCmdId.SCENE_CMD_ID_ANIMATED_MATERIAL_LIST: "SCENE_CMD_ANIMATED_MATERIAL_LIST",
    SceneCmdId.SCENE_CMD_ID_ACTOR_CUTSCENE_LIST: "SCENE_CMD_ACTOR_CUTSCENE_LIST",
    SceneCmdId.SCENE_CMD_ID_MAP_DATA: "SCENE_CMD_MAP_DATA",
    SceneCmdId.SCENE_CMD_ID_UNUSED_1D: "SCENE_CMD_UNUSED_1D",
    SceneCmdId.SCENE_CMD_ID_MAP_DATA_CHESTS: "SCENE_CMD_MAP_DATA_CHESTS",
}


class SceneCommandsResource(Resource, can_size_be_unknown=True):
    def __init__(self, file: File, range_start: int, name: str):
        super().__init__(file, range_start, None, name)
        self.parsed_commands: set[SceneCmdId] = set()
        self.player_entry_list_length = None
        self.room_list_length = None
        self.exit_list_length = None

    def try_parse_data(self, memory_context: "MemoryContext"):
        assert self.file.data is not None
        data = self.file.data[self.range_start :]

        new_progress_done = []
        waiting_for = []

        offset = 0
        cmd_id = None
        end_offset = None

        found_commands: set[SceneCmdId] = set()

        while offset + 8 <= len(data):
            cmd_id_int, data1, pad2, data2_I = struct.unpack_from(">BBHI", data, offset)
            _, data2_H0, data2_H1 = struct.unpack_from(">IHH", data, offset)
            _, data2_B0, data2_B1, data2_B2, data2_B3 = struct.unpack_from(
                ">IBBBB", data, offset
            )

            offset += 8
            cmd_id = SceneCmdId(cmd_id_int)
            assert pad2 == 0

            found_commands.add(cmd_id)

            if cmd_id == SceneCmdId.SCENE_CMD_ID_END:
                assert data1 == 0
                assert data2_I == 0
                end_offset = offset
                self.parsed_commands.add(cmd_id)
                break

            if cmd_id in self.parsed_commands:
                continue

            if cmd_id == SceneCmdId.SCENE_CMD_ID_ACTOR_LIST:
                resource = memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    scene_rooms_resources.ActorEntryListResource,
                    lambda file, offset: scene_rooms_resources.ActorEntryListResource(
                        file, offset, f"{self.name}_{data2_I:08X}_ActorEntryList"
                    ),
                )
                resource.set_length(data1)
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(("reported ActorEntryListResource", cmd_id))

            if cmd_id == SceneCmdId.SCENE_CMD_ID_OBJECT_LIST:
                resource = memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    scene_rooms_resources.ObjectListResource,
                    lambda file, offset: scene_rooms_resources.ObjectListResource(
                        file, offset, f"{self.name}_{data2_I:08X}_ObjectList"
                    ),
                )
                resource.set_length(data1)
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(("reported ObjectListResource", cmd_id))

            if cmd_id == SceneCmdId.SCENE_CMD_ID_ROOM_SHAPE:
                room_shape_resources.report_room_shape_at_segmented(
                    self, memory_context, data2_I, self.name
                )
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(("reported room shape resource", cmd_id))

            if cmd_id == SceneCmdId.SCENE_CMD_ID_ROOM_LIST:
                self.room_list_length = data1
                resource = memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    scene_rooms_resources.RoomListResource,
                    lambda file, offset: scene_rooms_resources.RoomListResource(
                        file, offset, f"{self.name}_{data2_I:08X}_RoomList"
                    ),
                )
                resource.set_length(data1)
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(("reported RoomListResource", cmd_id))

            if cmd_id == SceneCmdId.SCENE_CMD_ID_COL_HEADER:
                assert data1 == 0
                resource = memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    collision_resources.CollisionResource,
                    lambda file, offset: collision_resources.CollisionResource(
                        file, offset, f"{self.name}_{data2_I:08X}_Col"
                    ),
                )
                new_progress_done.append(("reported CollisionResource", cmd_id))
                if resource.is_data_parsed:
                    self.exit_list_length = resource.length_exitList
                    self.parsed_commands.add(cmd_id)
                    new_progress_done.append(
                        ("set self.exit_list_length from CollisionResource", cmd_id)
                    )
                else:
                    waiting_for.append(
                        (
                            "CollisionResource to be parsed to set self.exit_list_length",
                            cmd_id,
                            resource,
                        )
                    )

            if cmd_id == SceneCmdId.SCENE_CMD_ID_ENTRANCE_LIST:
                assert data1 == 0
                resource = memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    scene_rooms_resources.SpawnListResource,
                    lambda file, offset: scene_rooms_resources.SpawnListResource(
                        file, offset, f"{self.name}_{data2_I:08X}_SpawnList"
                    ),
                )
                new_progress_done.append(("reported SpawnListResource", cmd_id))
                if (
                    self.player_entry_list_length is not None
                    and self.room_list_length is not None
                ):
                    resource.player_entry_list_length = self.player_entry_list_length
                    resource.room_list_length = self.room_list_length
                    self.parsed_commands.add(cmd_id)
                    new_progress_done.append(
                        ("passed lengths to SpawnListResource", cmd_id)
                    )
                else:
                    waiting_for.append(
                        (
                            "self.player_entry_list_length and self.room_list_length"
                            " to pass to SpawnListResource",
                            cmd_id,
                        )
                    )

            if cmd_id == SceneCmdId.SCENE_CMD_ID_SPAWN_LIST:
                self.player_entry_list_length = data1
                resource = memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    scene_rooms_resources.ActorEntryListResource,
                    lambda file, offset: scene_rooms_resources.ActorEntryListResource(
                        file, offset, f"{self.name}_{data2_I:08X}_PlayerEntryList"
                    ),
                )
                resource.set_length(data1)
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(("reported ActorEntryListResource", cmd_id))

            if cmd_id == SceneCmdId.SCENE_CMD_ID_EXIT_LIST:
                assert data1 == 0
                resource = memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    scene_rooms_resources.ExitListResource,
                    lambda file, offset: scene_rooms_resources.ExitListResource(
                        file, offset, f"{self.name}_{data2_I:08X}_ExitList"
                    ),
                )
                new_progress_done.append(("reported ExitListResource", cmd_id))
                if self.exit_list_length is not None:
                    # TODO this doesnt work very well, eg need to trim to avoid overlaps
                    length = self.exit_list_length
                    # blindly align length to 2 (could/should check for zeros)
                    length = max(2, (length + 1) // 2 * 2)
                    # trim based on overlaps
                    while True:
                        _, other_resource = resource.file.get_resource_at(
                            resource.range_start
                            + length * resource.elem_cdata_ext.size
                            - 1
                        )
                        if other_resource is resource:
                            break
                        length -= 2
                    assert length > 0
                    resource.set_length(length)
                    self.parsed_commands.add(cmd_id)
                    new_progress_done.append(
                        ("passed length to ExitListResource", cmd_id, resource)
                    )
                else:
                    waiting_for.append(
                        (
                            "self.exit_list_length to (guess a length to) pass to ExitListResource",
                            cmd_id,
                        )
                    )

            if cmd_id == SceneCmdId.SCENE_CMD_ID_ENV_LIGHT_SETTINGS:
                resource = memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    scene_rooms_resources.EnvLightSettingsListResource,
                    lambda file, offset: scene_rooms_resources.EnvLightSettingsListResource(
                        file, offset, f"{self.name}_{data2_I:08X}_EnvLightSettingsList"
                    ),
                )
                resource.set_length(data1)
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(
                    ("reported EnvLightSettingsListResource", cmd_id)
                )

            if cmd_id == SceneCmdId.SCENE_CMD_ID_TRANSI_ACTOR_LIST:
                resource = memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    scene_rooms_resources.TransitionActorEntryListResource,
                    lambda file, offset: scene_rooms_resources.TransitionActorEntryListResource(
                        file,
                        offset,
                        f"{self.name}_{data2_I:08X}_TransitionActorEntryList",
                    ),
                )
                resource.set_length(data1)
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(
                    ("reported TransitionActorEntryListResource", cmd_id)
                )

            if cmd_id == SceneCmdId.SCENE_CMD_ID_PATH_LIST:
                assert data1 == 0
                memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    scene_rooms_resources.PathListResource,
                    lambda file, offset: scene_rooms_resources.PathListResource(
                        file, offset, f"{self.name}_{data2_I:08X}_PathList"
                    ),
                )
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(("reported PathListResource", cmd_id))

            if cmd_id == SceneCmdId.SCENE_CMD_ID_ALTERNATE_HEADER_LIST:
                assert data1 == 0
                memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    AltHeadersResource,
                    lambda file, offset: AltHeadersResource(
                        file, offset, f"{self.name}_{data2_I:08X}_AltHeaders"
                    ),
                )
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(("reported AltHeadersResource", cmd_id))

            if cmd_id == SceneCmdId.SCENE_CMD_ID_ANIMATED_MATERIAL_LIST:
                # TODO implement AnimatedMaterialListResource
                from ..extase import BinaryBlobResource

                assert data1 == 0
                memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    BinaryBlobResource,
                    lambda file, offset: BinaryBlobResource(
                        file,
                        offset,
                        offset + 4,
                        f"{self.name}_{data2_I:08X}_AnimatedMaterialList",
                    ),
                )
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(
                    ("reported AnimatedMaterialListResource", cmd_id)
                )

            if cmd_id == SceneCmdId.SCENE_CMD_ID_ACTOR_CUTSCENE_LIST:
                # TODO implement ActorCutsceneListResource
                from ..extase import BinaryBlobResource

                memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    BinaryBlobResource,
                    lambda file, offset: BinaryBlobResource(
                        file,
                        offset,
                        offset + 4,
                        f"{self.name}_{data2_I:08X}_ActorCutsceneList",
                    ),
                )
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(("reported ActorCutsceneListResource", cmd_id))

            if cmd_id == SceneCmdId.SCENE_CMD_ID_MAP_DATA:
                # TODO implement MapDataResource
                from ..extase import BinaryBlobResource

                memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    BinaryBlobResource,
                    lambda file, offset: BinaryBlobResource(
                        file,
                        offset,
                        offset + 4,
                        f"{self.name}_{data2_I:08X}_MapData",
                    ),
                )
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(("reported MapDataResource", cmd_id))

            if cmd_id == SceneCmdId.SCENE_CMD_ID_CUTSCENE_SCRIPT_LIST:
                # TODO implement CutsceneScriptListResource
                from ..extase import BinaryBlobResource

                memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    BinaryBlobResource,
                    lambda file, offset: BinaryBlobResource(
                        file,
                        offset,
                        offset + 4,
                        f"{self.name}_{data2_I:08X}_CutsceneScriptList",
                    ),
                )
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(
                    ("reported CutsceneScriptListResource", cmd_id)
                )

            if cmd_id == SceneCmdId.SCENE_CMD_ID_ACTOR_CUTSCENE_CAM_LIST:
                # TODO implement ActorCutsceneCamListResource
                from ..extase import BinaryBlobResource

                memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    BinaryBlobResource,
                    lambda file, offset: BinaryBlobResource(
                        file,
                        offset,
                        offset + 4,
                        f"{self.name}_{data2_I:08X}_ActorCutsceneCamList",
                    ),
                )
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(
                    ("reported ActorCutsceneCamListResource", cmd_id)
                )

            if cmd_id == SceneCmdId.SCENE_CMD_ID_MAP_DATA_CHESTS:
                # TODO implement MapDataChestsResource
                from ..extase import BinaryBlobResource

                memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    BinaryBlobResource,
                    lambda file, offset: BinaryBlobResource(
                        file,
                        offset,
                        offset + 4,
                        f"{self.name}_{data2_I:08X}_MapDataChests",
                    ),
                )
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(("reported MapDataChestsResource", cmd_id))

            if cmd_id == SceneCmdId.SCENE_CMD_ID_LIGHT_LIST:
                # TODO implement LightListResource
                from ..extase import BinaryBlobResource

                memory_context.report_resource_at_segmented(
                    self,
                    data2_I,
                    BinaryBlobResource,
                    lambda file, offset: BinaryBlobResource(
                        file,
                        offset,
                        offset + 4,
                        f"{self.name}_{data2_I:08X}_LightList",
                    ),
                )
                self.parsed_commands.add(cmd_id)
                new_progress_done.append(("reported LightListResource", cmd_id))

        if cmd_id != SceneCmdId.SCENE_CMD_ID_END:
            raise Exception("reached end of data without encountering end marker")
        assert end_offset is not None

        # Nothing to parse for these commands
        found_commands.discard(SceneCmdId.SCENE_CMD_ID_SOUND_SETTINGS)
        found_commands.discard(SceneCmdId.SCENE_CMD_ID_SPECIAL_FILES)
        found_commands.discard(SceneCmdId.SCENE_CMD_ID_SKYBOX_SETTINGS)
        found_commands.discard(SceneCmdId.SCENE_CMD_ID_TIME_SETTINGS)
        found_commands.discard(SceneCmdId.SCENE_CMD_ID_ROOM_BEHAVIOR)
        found_commands.discard(SceneCmdId.SCENE_CMD_ID_ECHO_SETTINGS)
        found_commands.discard(SceneCmdId.SCENE_CMD_ID_SKYBOX_DISABLES)
        found_commands.discard(SceneCmdId.SCENE_CMD_ID_WIND_SETTINGS)
        found_commands.discard(SceneCmdId.SCENE_CMD_ID_SET_REGION_VISITED)

        self.range_end = self.range_start + end_offset
        assert self.parsed_commands.issubset(found_commands)

        if found_commands - self.parsed_commands:
            if VERBOSE_NOT_FULLY_PARSED_SCENECMD:
                print("NOT FULLY PARSED:", self)
                print("Found commands:", found_commands)
                print("Parsed commands:", self.parsed_commands)
                print("FOUND BUT NOT PARSED:", found_commands - self.parsed_commands)

        if waiting_for:
            if new_progress_done:
                raise ResourceParseInProgress(
                    new_progress_done=new_progress_done, waiting_for=waiting_for
                )
            else:
                raise ResourceParseWaiting(waiting_for=waiting_for)

        assert self.parsed_commands == found_commands
        return RESOURCE_PARSE_SUCCESS

    def get_c_declaration_base(self):
        return f"SceneCmd {self.symbol_name}[]"

    def write_extracted(self, memory_context):
        assert self.file.data is not None
        data = self.file.data[self.range_start : self.range_end]
        with self.extract_to_path.open("w") as f:
            if not self.braces_in_source:
                f.write("{\n")
            for offset in range(0, len(data), 8):
                cmd_id_int, data1, pad2, data2_I = struct.unpack_from(
                    ">BBHI", data, offset
                )
                _, data2_B0, data2_B1, data2_B2, data2_B3 = struct.unpack_from(
                    ">IBBBB", data, offset
                )
                _, data2_b0, data2_b1, data2_b2, data2_b3 = struct.unpack_from(
                    ">Ibbbb", data, offset
                )
                cmd_id = SceneCmdId(cmd_id_int)
                f.write(" " * 4)
                f.write(scene_cmd_macro_name_by_cmd_id[cmd_id])
                f.write("(")
                if cmd_id == SceneCmdId.SCENE_CMD_ID_SPAWN_LIST:
                    address = data2_I
                    f.write(
                        memory_context.get_c_expression_length_at_segmented(address)
                    )
                    f.write(", ")
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_ACTOR_LIST:
                    address = data2_I
                    f.write(
                        memory_context.get_c_expression_length_at_segmented(address)
                    )
                    f.write(", ")
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_COL_HEADER:
                    assert data1 == 0
                    address = data2_I
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_ROOM_LIST:
                    address = data2_I
                    f.write(
                        memory_context.get_c_expression_length_at_segmented(address)
                    )
                    f.write(", ")
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_WIND_SETTINGS:
                    assert data1 == 0
                    xDir = data2_b0
                    yDir = data2_b1
                    zDir = data2_b2
                    strength = data2_B3
                    f.write(f"{xDir}, {yDir}, {zDir}, {strength}")
                if cmd_id == SceneCmdId.SCENE_CMD_ID_ENTRANCE_LIST:
                    assert data1 == 0
                    address = data2_I
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_SPECIAL_FILES:
                    naviQuestHintFileId = data1
                    keepObjectId = data2_I
                    f.write(
                        f"{oot64_data.get_navi_quest_hint_file_id_name(naviQuestHintFileId)}, "
                        f"{oot64_data.get_object_id_name(keepObjectId)}"
                    )
                if cmd_id == SceneCmdId.SCENE_CMD_ID_ROOM_BEHAVIOR:
                    gpFlags1 = data1
                    gpFlags2 = data2_I

                    # define SCENE_CMD_ROOM_BEHAVIOR(type, environment, lensMode, msgCtxunk12044, enablePosLights, stormState)
                    type = gpFlags1
                    environment = _SHIFTR(gpFlags2, 0, 8)
                    lensMode = _SHIFTR(gpFlags2, 8, 1)
                    msgCtxunk12044 = _SHIFTR(gpFlags2, 10, 1)
                    enablePosLights = _SHIFTR(gpFlags2, 11, 1)
                    stormState = _SHIFTR(gpFlags2, 12, 1)
                    type_name = oot64_data.get_room_behavior_type_name(type)
                    environment_name = oot64_data.get_room_behavior_environment_name(
                        environment
                    )
                    lensMode_name = oot64_data.get_lens_mode_name(lensMode)
                    f.write(
                        f"{type_name}, {environment_name}, {lensMode_name}, {msgCtxunk12044}, {enablePosLights}, {stormState}"
                    )
                if cmd_id == SceneCmdId.SCENE_CMD_ID_UNK_09:
                    assert data1 == 0
                    assert data2_I == 0
                if cmd_id == SceneCmdId.SCENE_CMD_ID_ROOM_SHAPE:
                    assert data1 == 0  # TODO these asserts should be done on parse?
                    address = data2_I
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_OBJECT_LIST:
                    address = data2_I
                    f.write(
                        memory_context.get_c_expression_length_at_segmented(address)
                    )
                    f.write(", ")
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_LIGHT_LIST:
                    numLights = data1
                    address = data2_I
                    f.write(f"{numLights}, ")
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_PATH_LIST:
                    assert data1 == 0
                    address = data2_I
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_TRANSI_ACTOR_LIST:
                    address = data2_I
                    f.write(
                        memory_context.get_c_expression_length_at_segmented(address)
                    )
                    f.write(", ")
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_ENV_LIGHT_SETTINGS:
                    address = data2_I
                    f.write(
                        memory_context.get_c_expression_length_at_segmented(address)
                    )
                    f.write(", ")
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_TIME_SETTINGS:
                    assert data1 == 0
                    hour = data2_B0
                    min_ = data2_B1
                    timeSpeed = data2_B2
                    assert data2_B3 == 0

                    hour_str = "0xFF" if hour == 0xFF else str(hour)
                    min_str = "0xFF" if min_ == 0xFF else str(min_)
                    timeSpeed_str = "0xFF" if timeSpeed == 0xFF else str(timeSpeed)

                    if hour == 0xFF or min_ == 0xFF:
                        f.write("/* don't set time */ ")
                    f.write(f"{hour_str}, {min_str}, {timeSpeed_str}")
                    if timeSpeed == 0xFF or timeSpeed == 0:
                        f.write(" /* time doesn't move */")
                if cmd_id == SceneCmdId.SCENE_CMD_ID_SKYBOX_SETTINGS:
                    externalTextureFileId = data1
                    skyboxId = data2_B0
                    skyboxConfig = data2_B1
                    envLightMode = data2_B2
                    assert data2_B3 == 0
                    f.write(
                        f"{externalTextureFileId}, "  # TODO symbolize
                        f"{oot64_data.get_skybox_id(skyboxId)}, "
                        f"{skyboxConfig}, "
                        f"{oot64_data.get_light_mode(envLightMode)}"
                    )
                if cmd_id == SceneCmdId.SCENE_CMD_ID_SKYBOX_DISABLES:
                    assert data1 == 0
                    skyboxDisabled = data2_B0
                    sunMoonDisabled = data2_B1
                    assert data2_B2 == data2_B3 == 0
                    skyboxDisabled_name = (
                        "true /* no skybox */"
                        if skyboxDisabled
                        else "false /* skybox enabled */"
                    )
                    sunMoonDisabled_name = (
                        "true /* no sun/moon */"
                        if sunMoonDisabled
                        else "false /* sun/moon enabled */"
                    )
                    f.write(f"{skyboxDisabled_name}, {sunMoonDisabled_name}")
                if cmd_id == SceneCmdId.SCENE_CMD_ID_EXIT_LIST:
                    assert data1 == 0
                    address = data2_I
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_END:
                    assert data1 == 0
                    assert data2_I == 0
                if cmd_id == SceneCmdId.SCENE_CMD_ID_SOUND_SETTINGS:
                    specId = data1
                    assert data2_B0 == 0
                    assert data2_B1 == 0
                    ambienceId = data2_B2
                    seqId = data2_B3
                    ambienceId_name = oot64_data.get_ambience_id_name(ambienceId)
                    seqId_name = oot64_data.get_sequence_id_name(seqId)
                    f.write(f"{specId}, {ambienceId_name}, {seqId_name}")
                if cmd_id == SceneCmdId.SCENE_CMD_ID_ECHO_SETTINGS:
                    assert data1 == 0
                    assert data2_B0 == data2_B1 == data2_B2 == 0
                    echo = data2_B3
                    f.write(f"{echo}")
                if cmd_id == SceneCmdId.SCENE_CMD_ID_ALTERNATE_HEADER_LIST:
                    assert data1 == 0
                    address = data2_I
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_CUTSCENE_SCRIPT_LIST:
                    numEntries = data1
                    address = data2_I
                    f.write(f"{numEntries}, ")
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_ACTOR_CUTSCENE_LIST:
                    numEntries = data1
                    address = data2_I
                    f.write(f"{numEntries}, ")
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_ACTOR_CUTSCENE_CAM_LIST:
                    numCams = data1
                    address = data2_I
                    f.write(f"{numCams}, ")
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_MAP_DATA:
                    assert data1 == 0
                    address = data2_I
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_ANIMATED_MATERIAL_LIST:
                    assert data1 == 0
                    address = data2_I
                    f.write(memory_context.get_c_reference_at_segmented(address))
                if cmd_id == SceneCmdId.SCENE_CMD_ID_MAP_DATA_CHESTS:
                    chestCount = data1
                    address = data2_I
                    f.write(f"{chestCount}, ")
                    f.write(memory_context.get_c_reference_at_segmented(address))

                f.write("),\n")

            if not self.braces_in_source:
                f.write("}\n")

    def get_c_reference(self, resource_offset: int):
        if resource_offset == 0:
            return self.symbol_name
        else:
            raise ValueError

    def get_c_includes(self):
        return (
            "array_count.h",
            Z64HDRPRFX + "object.h",  # for OBJECT_*
            # TODO these are not always needed:
            "sequence.h",  # for NATURE_ID_* and NA_BGM_*
            Z64HDRPRFX + "skybox.h",  # for SKYBOX_*
        )

    def get_h_includes(self):
        return (Z64HDRPRFX + "scene.h",)


class AltHeadersResource(CDataArrayResource):
    def report_elem(resource, memory_context: "MemoryContext", v):
        assert isinstance(v, int)
        address = v
        if address != 0:
            memory_context.report_resource_at_segmented(
                resource,
                address,
                SceneCommandsResource,
                lambda file, offset: SceneCommandsResource(
                    file, offset, f"{resource.name}_{address:08X}_Cmds"
                ),
            )

    def write_elem(
        resource, memory_context: "MemoryContext", v, wctx: CDataExtWriteContext
    ):
        assert isinstance(v, int)
        address = v
        wctx.f.write(wctx.line_prefix)
        if address == 0:
            wctx.f.write("NULL")
        else:
            wctx.f.write(memory_context.get_c_reference_at_segmented(address))
        return True

    elem_cdata_ext = (
        CDataExt_Value("I").set_report(report_elem).set_write(write_elem)
    )  # SceneCmd*

    def try_parse_data(self, memory_context):
        assert self.file.data is not None
        length = 0
        for i, (v,) in enumerate(
            struct.iter_unpack(">I", self.file.data[self.range_start :])
        ):
            if VERBOSE_ALT_HEADERS_GUESS_LENGTH:
                print(f"Considering {v:#X} at index {i}")
            if v == 0:
                # TODO iirc in OoT the first three alternate headers are required if there are alternate headers at all
                # so in OoT's equivalent of this code there's an exception here to increment i and continue if i < 3
                # what about MM?
                break

            try:
                resolve_result = memory_context.resolve_segmented(v)
            except:
                break
            data_may_be_scenecmds = False
            for j in range(
                resolve_result.file_offset, len(resolve_result.file.data), 8
            ):
                cmd_id_int = resolve_result.file.data[j]
                try:
                    cmd_id = SceneCmdId(cmd_id_int)
                except ValueError:
                    if VERBOSE_ALT_HEADERS_GUESS_LENGTH:
                        print("Invalid SceneCmdId", cmd_id_int)
                    break
                if cmd_id == SceneCmdId.SCENE_CMD_ID_END:
                    data_may_be_scenecmds = True
                    if VERBOSE_ALT_HEADERS_GUESS_LENGTH:
                        print(f"{v:#X} may be SceneCmd[]")
                    break
            if not data_may_be_scenecmds:
                break
            length = i + 1
        assert length > 0
        self.set_length(length)
        return super().try_parse_data(memory_context)

    def get_c_declaration_base(self):
        return f"SceneCmd* {self.symbol_name}[]"

    def get_h_includes(self):
        return (Z64HDRPRFX + "scene.h",)
