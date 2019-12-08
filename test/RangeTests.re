open EditorCoreTypes;
open TestFramework;

open Helpers;

let constantMeasure = (length, _: int) => length;

let r = (startLine, startCharacter, endLine, endCharacter) =>
  Range.create(
    ~startLine=Index.fromZeroBased(startLine),
    ~startCharacter=Index.fromZeroBased(startCharacter),
    ~endLine=Index.fromZeroBased(endLine),
    ~endCharacter=Index.fromZeroBased(endCharacter),
    (),
  );

describe("Range", ({describe, _}) =>
  describe("explode", ({test, _}) => {
    test(
      "returns same range when start line/endline are the same", ({expect}) => {
        let emptyRange = 
          Range.create(
            ~startLine=Index.zero,
            ~startCharacter=Index.zero,
            ~endLine=Index.zero,
            ~endCharacter=Index.zero,
            (),
          );

        validateRanges(
          expect,
          Range.explode(constantMeasure(1), emptyRange),
          [emptyRange],
        )
      });

    test("simple two-line case", ({expect}) => {
      let range = r(1, 5, 2, 2);

      validateRanges(
        expect,
        Range.explode(constantMeasure(10), range),
        [r(1, 5, 1, 9), r(2, 0, 2, 2)],
      );
    });

    test("uses range function", ({expect}) => {
      let range = r(1, 5, 3, 2);

      validateRanges(
        expect,
        Range.explode(constantMeasure(10), range),
        [r(1, 5, 1, 9), r(2, 0, 2, 9), r(3, 0, 3, 2)],
      );
    });
  })
);
