type t = pri int;

let fromZeroBased: int => t;
let fromOneBased: int => t;

let toZeroBased: t => int;
let toOneBased: t => int;

let equals: (t, t) => bool;