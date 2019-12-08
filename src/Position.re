[@deriving show({with_path: false})]
type t = {
  line: Index.t,
  character: Index.t,
};

let create = (line, character) => {line, character};

let equals = (a: t, b: t) => {
  Index.equals(a.line, b.line) && Index.equals(a.character, b.character);
};