[@deriving show({with_path: false})]
type t = {
  startPosition: Position.t,
  endPosition: Position.t,
};

let createFromPositions = (~startPosition, ~endPosition, ()) => {
  startPosition,
  endPosition,
};

let ofPositions = createFromPositions;

let create = (~startLine, ~startCharacter, ~endLine, ~endCharacter, ()) =>
  createFromPositions(
    ~startPosition=Position.create(startLine, startCharacter),
    ~endPosition=Position.create(endLine, endCharacter),
    (),
  );

let contains = (v: t, position: Position.t) => {
  let l0 = Index.toZeroBased(v.startPosition.line);
  let c0 = Index.toZeroBased(v.startPosition.character);
  let l1 = Index.toZeroBased(v.endPosition.line);
  let c1 = Index.toZeroBased(v.endPosition.character);

  let pl = Index.toZeroBased(position.line);
  let pc = Index.toZeroBased(position.character);

  (pl == l0 && pc >= c0 || pl > l0) && (pl == l1 && pc <= c1 || pl < l1);
};

let toZeroBasedPair = (v: Position.t) => {
  (Index.toZeroBased(v.line), Index.toZeroBased(v.character));
};

let explode = (measure, v) => {
  let (startLine, startCharacter) = v.startPosition |> toZeroBasedPair;
  let (endLine, endCharacter) = v.endPosition |> toZeroBasedPair;

  if (startLine == endLine) {
    [v];
  } else {
    let idx = ref(startLine);

    let ranges = ref([]);

    while (idx^ < endLine) {
      let i = idx^;

      let startCharacter = i == startLine ? startCharacter : 0;
      let endCharacter = max(0, measure(i) - 1);

      ranges :=
        [
          create(
            ~startLine=Index.fromZeroBased(i),
            ~startCharacter=Index.fromZeroBased(startCharacter),
            ~endCharacter=Index.fromZeroBased(endCharacter),
            ~endLine=Index.fromZeroBased(i),
            (),
          ),
          ...ranges^,
        ];

      incr(idx);
    };

    [
      create(
        ~startLine=Index.fromZeroBased(endLine),
        ~startCharacter=Index.fromZeroBased(0),
        ~endCharacter=Index.fromZeroBased(endCharacter),
        ~endLine=Index.fromZeroBased(endLine),
        (),
      ),
      ...ranges^,
    ]
    |> List.rev;
  };
};

let toHash = (ranges: list(t)) => {
  let rangeHash: Hashtbl.t(int, list(t)) = Hashtbl.create(100);
  List.iter(
    r => {
      let line = Index.toZeroBased(r.startPosition.line);

      let newVal =
        switch (Hashtbl.find_opt(rangeHash, line)) {
        | Some(v) => [r, ...v]
        | None => [r]
        };

      Hashtbl.add(rangeHash, line, newVal);
    },
    ranges,
  );

  rangeHash;
};

let equals = (a: t, b: t) => {
  Position.equals(a.startPosition, b.startPosition)
  && Position.equals(a.endPosition, b.endPosition);
};

let isInRange = (range: t, position: Position.t) => {
  (
    position.line == range.startPosition.line
    && position.character >= range.startPosition.character
    || position.line > range.startPosition.line
  )
  && (
    position.line == range.endPosition.line
    && position.character <= range.endPosition.character
    || position.line < range.endPosition.line
  );
};