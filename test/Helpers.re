open EditorCoreTypes;

let validateRange =
    (
      expect: Rely__DefaultMatchers.matchers(unit),
      actualRange: Range.t,
      expectedRange: Range.t,
    ) => {
  expect.int(Index.toZeroBasedInt(actualRange.startPosition.line)).toBe(
    Index.toZeroBasedInt(expectedRange.startPosition.line),
  );
  expect.int(Index.toZeroBasedInt(actualRange.endPosition.line)).toBe(
    Index.toZeroBasedInt(expectedRange.endPosition.line),
  );
  expect.int(Index.toZeroBasedInt(actualRange.startPosition.character)).toBe(
    Index.toZeroBasedInt(expectedRange.startPosition.character),
  );
  expect.int(Index.toZeroBasedInt(actualRange.endPosition.character)).toBe(
    Index.toZeroBasedInt(expectedRange.endPosition.character),
  );
};

let validateRanges =
    (
      expect: Rely__DefaultMatchers.matchers(unit),
      actualRanges,
      expectedRanges,
    ) => {
  List.iter2(validateRange(expect), actualRanges, expectedRanges);
};
