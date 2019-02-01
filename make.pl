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
$verbose=1;
#$optimize=1;

unless ($#ARGV > -1) {
    make_all();
}
else{
    if($ARGV[0] eq "clean"){
        clean();
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
    libs();
    build();
}

sub libs{
    print "libs\n" if $verbose;
    `mkdir -p lib`;
    chdir "src";
    `gcc -O3 -c *.c -Wfatal-errors -lncurses -lm` if $optimize;
    `gcc -c *.c -Wfatal-errors -lncurses -lm` unless $optimize;
    `ar rcs libezdash.a *.o`;
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
        "gcc -O3 test/main.c $lib_string -Llib -Isrc -o bin/test -lncurses -lm lezdash"
        if $optimize;
    $build_string =
        "gcc test/main.c $lib_string -Llib -Isrc -o bin/test -lm -lncurses"
        unless $optimize;
    `$build_string`;
}

sub clean{
    print "clean\n" if $verbose;
    `rm -rf lib`;
    `rm -rf bin`;
}


