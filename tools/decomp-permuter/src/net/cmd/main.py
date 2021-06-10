from argparse import ArgumentParser, RawDescriptionHelpFormatter
import sys

from ..core import ServerError, enable_debug_mode
from .run_server import RunServerCommand
from .setup import SetupCommand
from .ping import PingCommand
from .vouch import VouchCommand


def main() -> None:
    try:
        # We currently sometimes log stuff to stdout, so it's preferable if it's
        # line-buffered even when redirected to a non-tty (e.g. when running a
        # permuter server as a systemd service). This is supported by Python 3.7
        # and up.
        sys.stdout.reconfigure(line_buffering=True)  # type: ignore
    except Exception:
        pass

    parser = ArgumentParser(
        description="permuter@home - run the permuter across the Internet!\n\n"
        "To use p@h as a client, just pass -J when running the permuter. "
        "This script is\nonly necessary for configuration or when running a server.",
        formatter_class=RawDescriptionHelpFormatter,
    )

    commands = [
        PingCommand,
        RunServerCommand,
        SetupCommand,
        VouchCommand,
    ]

    parser.add_argument(
        "--debug",
        dest="debug",
        action="store_true",
        help="Enable debug logging.",
    )

    subparsers = parser.add_subparsers(metavar="<command>")
    for command in commands:
        subparser = subparsers.add_parser(
            command.command,
            help=command.help,
            description=command.help,
        )
        command.add_arguments(subparser)
        subparser.set_defaults(subcommand_handler=command.run)

    args = parser.parse_args()
    if args.debug:
        enable_debug_mode()

    if "subcommand_handler" in args:
        try:
            args.subcommand_handler(args)
        except EOFError as e:
            print("Network error:", e)
            sys.exit(1)
        except ServerError as e:
            print("Error:", e.message)
            sys.exit(1)
    else:
        parser.print_help()


if __name__ == "__main__":
    main()
