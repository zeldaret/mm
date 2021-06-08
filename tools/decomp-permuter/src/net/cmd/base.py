import abc
from argparse import ArgumentParser, Namespace


class Command(abc.ABC):
    command: str
    help: str

    @staticmethod
    @abc.abstractmethod
    def add_arguments(parser: ArgumentParser) -> None:
        ...

    @staticmethod
    @abc.abstractmethod
    def run(args: Namespace) -> None:
        ...
