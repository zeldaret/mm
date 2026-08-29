# SPDX-FileCopyrightText: © 2025 ZeldaRET
# SPDX-License-Identifier: CC0-1.0

from typing import Sequence

I_D_OMEGALUL = True


from . import actor_ids


def get_actor_id_name(actor_id: int) -> str:
    if actor_id < 0 or actor_id >= len(actor_ids.DATA):
        raise ValueError(f"Unknown {actor_id=}")
    return actor_ids.DATA[actor_id]


from . import object_ids


def get_object_id_name(object_id: int) -> str:
    return object_ids.DATA[object_id]


from . import scene_table_mini


def get_scene_rom_file_name(scene_id: int) -> str:
    return scene_table_mini.DATA[scene_id][0]


def get_scene_id_name(scene_id: int) -> str:
    return scene_table_mini.DATA[scene_id][1]


scene_id_by_rom_file_name = {
    rom_file_name: scene_id
    for scene_id, (rom_file_name, scene_id_name) in enumerate(scene_table_mini.DATA)
}


def get_scene_id_from_rom_file_name(rom_file_name: str) -> int:
    return scene_id_by_rom_file_name[rom_file_name]


from . import audio_ids


def get_sequence_id_name(sequence_id: int) -> str:
    return audio_ids.SEQ_IDS[sequence_id]


def get_ambience_id_name(ambience_id: int) -> str:
    return audio_ids.AMBIENCE_IDS[ambience_id]


from . import misc_ids


def get_scene_cam_type_name(scene_cam_type: int) -> str:
    return misc_ids.SCENE_CAM_TYPES[scene_cam_type]


def get_room_behavior_type_name(type: int) -> str:
    return misc_ids.ROOM_BEHAVIOR_TYPE_NAMES[type]


def get_room_behavior_environment_name(environment: int) -> str:
    return misc_ids.ROOM_BEHAVIOR_ENVIRONMENT_NAMES[environment]


def get_lens_mode_name(lens_mode: int) -> str:
    return misc_ids.LENS_MODES[lens_mode]


def get_camera_setting_type_name(camera_setting_type: int) -> str:
    return misc_ids.CAMERA_SETTING_TYPES[camera_setting_type]


def get_room_shape_type_name(room_shape_type: int) -> str:
    return misc_ids.ROOM_SHAPE_TYPE[room_shape_type]


def get_room_shape_image_amount_type_name(room_shape_image_amount_type: int) -> str:
    return misc_ids.ROOM_SHAPE_IMAGE_AMOUNT_TYPE[room_shape_image_amount_type]


def get_skybox_id(skybox_id: int) -> str:
    return misc_ids.SKYBOX_IDS[skybox_id]


def get_light_mode(light_mode: int) -> str:
    return misc_ids.LIGHT_MODES[light_mode]


def get_navi_quest_hint_file_id_name(navi_quest_hint_file_id: int) -> str:
    return misc_ids.NAVI_QUEST_HINT_FILE_IDS[navi_quest_hint_file_id]
