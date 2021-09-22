from dataclasses import dataclass


@dataclass
class ServerError(Exception):
    message: str


@dataclass
class CandidateConstructionFailure(Exception):
    message: str
