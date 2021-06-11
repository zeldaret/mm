import attr


@attr.s
class CandidateConstructionFailure(Exception):
    message: str = attr.ib()
