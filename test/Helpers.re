open EditorCoreTypes;

let validateRange =
    (
      expect: Rely__DefaultMatchers.matchers(unit),
      actualRange: Range.t,
      expectedRange: Range.t,
    ) => {
  expect.int(Index.toZeroBased(actualRange.startPosition.line)).toBe(
    Index.toZeroBased(expectedRange.startPosition.line),
  );
  expect.int(Index.toZeroBased(actualRange.endPosition.line)).toBe(
    Index.toZeroBased(expectedRange.endPosition.line),
  );
  expect.int(Index.toZeroBased(actualRange.startPosition.character)).toBe(
    Index.toZeroBased(expectedRange.startPosition.character),
  );
  expect.int(Index.toZeroBased(actualRange.endPosition.character)).toBe(
    Index.toZeroBased(expectedRange.endPosition.character),
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
