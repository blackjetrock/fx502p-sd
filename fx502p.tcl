#!/usr/bin/wish
#
# Script that processes the fx502p files that come from the SD card gadget
#
#

set ::KEYWORDS {
    P0
    P1
    P2
    P3
    P4
    P5
    P6
    P7
    P8
    P9
    0
    1
    2
    3
    .
    EXP
    RND0
    RND1
    RND2
    RND3
    RND4
    RND5
    RND6
    RND7
    RND8
    RND9
    4
    5
    6
    7
    8
    9
    LBL0
    LBL1
    LBL2
    LBL3
    LBL4
    LBL5
    LBL6
    LBL7
    LBL8
    LBL9
    HLT
    "\""
	20+
    40+
    60+
    ?2F
    GOTO0
    GOTO1
    GOTO2
    GOTO3
    GOTO4
    GOTO5
    GOTO6
    GOTO7
    GOTO8
    GOTO9
    xD
    ?3B
    ENG
    DMS
    LOG
    LN
    GSBP0
    GSBP1
    GSBP2
    GSBP3
    GSBP4
    GSBP5
    GSBP6
    GSBP7
    GSBP8
    GSBP9
    +/-
    (
     )
    SIN
    COS
    TAN
    X<>M00
    X<>M01
    X<>M02
    X<>M03
    X<>M04
    X<>M05
    X<>M06
    X<>M07
    X<>M08
    X<>M09
    *
    /
    +
    -
    =
    EXE
    Min00
    Min01
    Min02
    Min03
    Min04
    Min05
    Min06
    Min07
    Min08
    Min09
    ?6A
    DSZ
    X=0
    X=F
    RND#
    PI
    MR00
    MR01
    MR02
    MR03
    MR04
    MR05
    MR06
    MR07
    MR08
    MR09
    ISZ
    x>=0
    x>=F
    MEANX
    SDX
    SDXN
    M-00
    M-01
    M-02
    M-03
    M-04
    M-05
    M-06
    M-07
    M-08
    M-09
    PAUSE
    IND
    SAVE
    LOAD
    MAC
    SAC
    M+00
    M+01
    M+02
    M+03
    M+04
    M+05
    M+06
    M+07
    M+08
    M+09
    XDEL
    ?9B
    SENG
    SDMS
    10^X
    e^X
    X<>M10
    X<>M11
    X<>M12
    X<>M13
    X<>M14
    X<>M15
    X<>M16
    X<>M17
    X<>M18
    X<>M19
    ABS
    INT
    FRAC
    ASN
    ACS
    ATN
    Min10
    Min11
    Min12
    Min13
    Min14
    Min15
    Min16
    Min17
    Min18
    Min19
    X^Y
    X^(1/Y)
    R>P
    P>R
    %
    SEXE
    MR10
    MR11
    MR12
    MR13
    MR14
    MR15
    MR16
    MR17
    MR18
    MR19
    GSB(0)
    X<>Y
    SQR
    X^2
    1/X
    X!
    M-10
    M-11
    M-12
    M-13
    M-14
    M-15
    M-16
    M-17
    M-18
    M-19
    DEG
    RAD
    GRA
    HYPSIN
    HYPCOS
    HYPTAN
    M+10
    M+11
    M+12
    M+13
    M+14
    M+15
    M+16
    M+17
    M+18
    M+19
    ?EA
    ?EB
    ?EC
    HYPASN
    HYPACS
    HYPATN
    X<>MF
    MinF
    MRF
    M-F
    M+F
    ?F5
    Min1F
    MR1F
    M-1F
    M+1F
    AC
    ?FB
    ?FC
    ?FD
    ?FE
    ?FF
}

puts $::KEYWORDS

for {set i 0} {$i <256} {incr i 1} {
    puts [format "%02X: '%s'" $i [lindex $::KEYWORDS $i]]
}

# Bit reverses a number
proc reverse {x n} {
    set r 0

    for {set i 0} {$i < $n} {incr i 1} {
	set r [expr ($r << 1) | ($x & 1)]
	set x [expr $x >> 1]
    }
    
    return $r
}

proc open_file_window {w fn} {
    toplevel $w
    
    set f [open $fn]
    set filetext [read $f]
    close $f
    
    set width 80
    set height 40
    
    text $w.text -xscrollcommand [list $w.xscroll set] -yscrollcommand [list $w.yscroll set] -width $width -height $height
    scrollbar $w.xscroll -orient horizontal -command [list $w.text xview]
    scrollbar $w.yscroll -orient vertical -command [list $w.text yview]
    grid $w.text $w.yscroll -sticky news
    grid $w.xscroll -sticky news
    grid rowconfigure    $w 0 -weight 1
    grid columnconfigure $w 0 -weight 1

    # Put the data in the window and decode it as we go along
    set widx 0
    set program_file 0
    set memory_file 0
    
    foreach line [split $filetext "\n"] {
	if { [string length $line] > 0 } {
	    set v [expr 0x$line >> 4]

	    # Decode the nibbles in the line
	    set s  [expr ($v & 0x800) >> 11]
	    set n1 [expr ($v & 0x780) >> 7]
	    set n2 [expr ($v & 0x078) >> 3]
	    set pa [expr ($v & 0x004) >> 2]
	    set st [expr ($v & 0x003) >> 0]
	    set n1 [reverse $n1 4]
	    set n2 [reverse $n2 4]
	    set st [reverse $st 2]

	    set index [expr $n2*16+$n1]
	    set kw [lindex $::KEYWORDS $index]

	    switch $widx {
		0 {
		    incr widx 1
		    set hexval [format "%04X %d %01X %01X %d %01X %01X%01X"  $v $s $n1 $n2 $pa $st $n2 $n1 $kw]
		    set fn2 $n1
		    set fn1 $n2
		}

		1 {
		    incr widx 1

		    set fn0 $n1
		    
		    # n2 has file type:
		    switch $n2 {
			11 {
			    set filetype "Programs"
			    set program_file 1
			}
			15 {
			    set filetype "Memories"
			    set memory_file 1
			}
			default {
			    set filetype "Unknown file type $n2"
			}
			
		    }
		    set filenumber [format "%X%X%X" $fn0 $fn1 $fn2]
		    set hexval [format "%04X %d %01X %01X %d %01X %01X%01X  %s File:%s"  $v $s $n1 $n2 $pa $st $n2 $n1 $filetype $filenumber]

		    puts "File type:$filetype"
		}

		default {
		    if { $program_file } {
			set hexval [format "%04X %d %01X %01X %d %01X %01X%01X  %s"  $v $s $n1 $n2 $pa $st $n2 $n1 $kw]
		    }
		    if { $memory_file } {
			set mn [expr ($widx-2) / 8]
			switch $mn {
			    0 {
				set mns "F"
			    }
			    default {
				set mns [expr $mn - 1]
			    }
			    

			}
			
			set hexval [format "%04X %d %01X %01X %d %01X %01X%01X %d %s"  $v $s $n1 $n2 $pa $st $n2 $n1 $mn $mns]
		    }
		    incr widx 1
		}
	    }
	    

	    $w.text insert end "$hexval\n"
	}
    }
}


#
# Put up a list of all the FX502P files, so they can be viewed
#

proc display_files {w width height} {
    
    #frame $w
    text $w.text -xscrollcommand [list $w.xscroll set] -yscrollcommand [list $w.yscroll set] -width $width -height $height
    scrollbar $w.xscroll -orient horizontal -command [list $w.text xview]
    scrollbar $w.yscroll -orient vertical -command [list $w.text yview]
    grid $w.text $w.yscroll -sticky news
    grid $w.xscroll -sticky news
    grid rowconfigure    $w 0 -weight 1
    grid columnconfigure $w 0 -weight 1

    set f [glob "\{M,P\}*.DAT"]

    $w.text insert end "FX-502P Files\n"
    
    foreach file $f {
	$w.text insert end "$file\n"
	puts $file
    }

    return $w.text
}

proc write_data {a} {
    puts $a
}

proc open_main_window {w} {
    frame $w
    eval {text $w.text \
	      -xscrollcommand [list $w.xscroll set] \
	      -yscrollcommand [list $w.yscroll set]} -width 135 -height 50
    scrollbar $w.xscroll -orient horizontal \
	-command [list $w.text xview]
    scrollbar $w.yscroll -orient vertical \
	-command [list $w.text yview]
    grid $w.text $w.yscroll -sticky news
    grid $w.xscroll -sticky news
    grid rowconfigure    $w 0 -weight 1
    grid columnconfigure $w 0 -weight 1
    
    bind $w.text <Any-Key> "write_data %A"
    
    
    #Main menu
    menu $w.menu -tearoff 0
    
    $w.menu add cascade -label "File"   -menu $w.menu.file -underline 0
    $w.menu add cascade -label "FX502P" -menu $w.menu.fx502p -underline 0
    $w.menu add cascade -label "About"  -menu $w.menu.about -underline 0
    
    menu $w.menu.file -tearoff 0
    menu $w.menu.fx502p -tearoff 0
    menu $w.menu.about -tearoff 0
    
    set m $w.menu.file
    $m add command -label "Send IHX File" -command {send_ihx_file_dialog}
    $m add command -label "Exit" -command exit
    
    set m $w.menu.fx502p
    $m add command -label "Files" -command {display_files .files 80 40}
    
    set m $w.menu.about
    $m add command -label "FX-502P File Utility"
    $m add command -label "Version 1.0"
    
    . configure -menu $w.menu
    
    return $w.text
}

toplevel .files

open_main_window .t
pack .t -side top -fill both -expand true

# See if a filename was specified
if { [llength $argv] > 0 } {

    # Open the file and decode it
    open_file_window .filedata [lindex $argv 0]
    
}
