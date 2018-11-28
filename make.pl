# make.pl
#
# Use this to build zebra on any standard *nix with GCC
#
# Use at your own risk. I use Perl instead of autotools because the latter
#    are an opaque morass of Mad Hatter gibberish.
#
#   USAGE:
#
#   Build all:
#       perl make.pl
#
#   Clean:
#       perl make.pl clean
#$verbose=1;
$optimize=1;

unless ($#ARGV > -1) {
    make_all();
}
else{
    if($ARGV[0] eq "clean"){
        clean();
    }
    elsif($ARGV[0] eq "clean_all"){
        clean_all();
    }
    elsif($ARGV[0] eq "lib_babel"){
        lib_babel();
    }
    elsif($ARGV[0] eq "all_libs"){
        all_libs();
    }
    elsif($ARGV[0] eq "libs"){
        libs();
    }
    elsif($ARGV[0] eq "all"){
        make_all();
    }
}

sub make_all{
    print "make_all\n" if $verbose;
    all_libs();
    build();
}

sub all_libs{
    print "all_libs\n" if $verbose;
    `mkdir -p lib`;
    lib_babel();
    sat_tools();
    libs();
}

sub lib_babel{
    print "lib_babel\n" if $verbose;
    chdir "lib_babel";
    `perl make.pl libs`;
    chdir "../";
    `cp lib_babel/lib/libbabel.a lib`;
}

sub sat_tools{
    print "sat_tools\n" if $verbose;
    `mkdir -p sat_tools/lib`;
    `cp lib/libbabel.a sat_tools/lib`;
    chdir "sat_tools";
    `perl make.pl libs`;
    chdir "../";
    `cp sat_tools/lib/libsat_tools.a lib`;
}

sub libs{
    return; # do nothing
    print "libs\n" if $verbose;
    `mkdir -p lib`;
    chdir "src";
    `gcc -O3 -c *.c -I../lib_babel/src -I../sat_tools/src -Wfatal-errors -lm` if $optimize;
    `gcc -c *.c -I../lib_babel/src -I../sat_tools/src -Wfatal-errors -lm` unless $optimize;
    `ar rcs libzeppelin.a *.o`;
    `mv *.o ../lib`;
    `mv *.a ../lib`;
    chdir "../";
}

sub build{
    print "build\n" if $verbose;
    `mkdir -p bin`;
    my @libs = `ls lib`;
    my $lib_string = "";
    for(@libs){ chomp $_; $lib_string .= "lib/$_ " };
    my $build_string;
    $build_string =
        "gcc -O3 test/main.c $lib_string -Llib -lbabel -lsat_tools -Isrc -Ilib_babel/src -Isat_tools/src -o bin/test -lm"
        if $optimize;
    $build_string =
        "gcc test/main.c $lib_string -Llib -lbabel -lsat_tools -Isrc -Ilib_babel/src -Isat_tools/src -o bin/test -lm"
        unless $optimize;
    `$build_string`;
}

sub clean_all{
    print "clean_all\n" if $verbose;
    chdir "lib_babel";
    `perl make.pl clean`;
    chdir "../sat_tools";
    `perl make.pl clean`;
    chdir "../";
    clean();
}

sub clean{
    print "clean\n" if $verbose;
    `rm -rf lib`;
    `rm -rf bin`;
}


