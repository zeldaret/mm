import argparse
from pathlib import Path

from version import version_config
from text import msgdis

def main():
    parser = argparse.ArgumentParser(description="Extract text from the baserom into .h files")
    parser.add_argument(
        "baserom_segments_dir",
        type=Path,
        help="Directory of uncompressed ROM segments",
    )
    parser.add_argument(
        "output_dir",
        type=Path,
        help="Output directory to place files in",
    )
    parser.add_argument(
        "-v",
        "--version",
        help="version to process",
        default="n64-us",
    )
    args = parser.parse_args()

    baserom_segments_dir : Path = args.baserom_segments_dir
    version : str = args.version
    output_dir : Path = args.output_dir

    config = version_config.load_version_config(version)

    version_info = msgdis.GameVersionInfo(config.dmadata_segments["code"].vram, config.variables)

    msgdis.extract(version_info, baserom_segments_dir, output_dir)

if __name__ == '__main__':
    main()
