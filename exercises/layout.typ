#let layout(it) = {
  let abbr(it) = smallcaps(lower(it))

  show "FramboOS": smallcaps
  show "GitHub": smallcaps
  show "Raspberry Pi": smallcaps

  show "UART": abbr
  show "TCB": abbr
  show "PCB": abbr
  show "CPU": abbr
  show "SP": abbr
  show "PC": abbr
  show "LR": abbr
  show "CPSR": abbr
  show "ARM": abbr

  set raw(lang: "c")

  it
}
