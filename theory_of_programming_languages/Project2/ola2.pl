#### Author:      Ryan Florida
#### Program:     OLA2
#### File:        ola2.pl
#### Date:        April 10, 2017
#### Description: This program will implement two classes in order to maintain
####              a roster of students with associated information about those
####              students (c-number, grades, etc). In this particular file, 
####              the user can label the roster however they please, choose 
####              their desired input file, then they are prompted to enter a 
####              specific student's c-number so as to see that student's 
####              information. Once all of this is done, the entire roster
####              (ie all of the student information) is displayed for the
####              user. Written in the Perl programming language.

use lib 'lib';
use Roster;
use warnings;
use strict;

#0: Main.
sub main
{
	#Clear terminal window to enhance asthetics.
	system('clear');
	
	#Declare instance of Roster class, namely a CSCI 3210 roster.
	my $theoryRoster = Roster->new('3210');

	#Prompt user for input file containing roster data.
	print "Please enter the roster file: ";
	my $inputFile = <STDIN>;

	#Read the input file into the roster object.
	$theoryRoster->readStudentRecord($inputFile);

	#Prompt the user to query about two students on the roster, then display
	#the appropriate information.
	for(my $i = 0; $i < 2; $i++)
	{
        print "Please input a valid c-number: ";
     	my $c_number = <STDIN>;
     	print "\n";
     	$theoryRoster->printStudentInformation($c_number);
    }

    #Print the entire roster.
    $theoryRoster->printRoster();

    return;
}

#Call main.
main();