[bits 64]

;This file's author is KeepKonect.
;All credits go to him

GLOBAL LoadTSS

LoadTSS: ; RDI=offset
    ltr di
    ret