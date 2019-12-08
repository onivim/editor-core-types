[@deriving show({with_path: false})]
type t = {
  startPosition: Location.t,
  endPosition: Location.t,
};

let contains: (t, Location.t) => bool;

let createFromPositions:
  (~startPosition: Location.t, ~endPosition: Location.t, unit) => t;

let ofPositions:
  (~startPosition: Location.t, ~endPosition: Location.t, unit) => t;

let create:
  (
    ~startLine: Index.t,
    ~startCharacter: Index.t,
    ~endLine: Index.t,
    ~endCharacter: Index.t,
    unit
  ) =>
  t;

/*
 * explode(range, measure) takes a Range.t and a measurement function (int => int),
 * and expands a multiple-line range into a list of ranges, where there there is
 * a single range per-line.
 *
 * If the input range is a single line, a single item list with the input range
 * will be returned.
 */
let explode: (int => int, t) => list(t);

/**
 * [toHash(ranges)] takes a list [ranges] of [Range.t], and returns them as a
 * a hash table, where the key is the 0-based startLine of the [Range.t],
 * and the value is the list of all ranges with that startLine.
 */
let toHash: list(t) => Hashtbl.t(int, list(t));

let equals: (t, t) => bool;

let isInRange: (t, Location.t) => bool;