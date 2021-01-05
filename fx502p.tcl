#!/usr/bin/wish
#
# Script that processes the fx502p files that come from the SD card gadget
#
#

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
    foreach line [split $filetext "\n"] {
	if { [string length $line] > 0 } {
	    set v [expr 0x$line >> 4]
	    
	    $w.text insert end "$line\n"
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

    set f [glob "FILE*.DAT"]

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
