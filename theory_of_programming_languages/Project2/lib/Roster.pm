#### Author:      Ryan Florida
#### Program:     OLA2
#### File:        Roster.pm
#### Date:        April 10, 2017
#### Description: This file is part of the second open lab assignment, which
####              includes ola2.pl, Student.pm, and Roster.pm. This file gives
####              the full definition of the class Roster.

use lib 'lib';
package Roster;
use Student;

#Constructor.
sub new{

 	my $class = shift;
 	my $this = {
 		#Member data to be initialized when object is instantiated.
 		courseName => shift
 	};

 	#Member data to be filled in appropriately later.
 	$this->{studentNum} = 0;
 	$this->{studentArray} = [];

 	#Give Roster class properties.
 	bless $this, $class;

 	return $this;
 }

#******************************************************************************
#This subroutine reads the input file into the array of Student type objects.
sub readStudentRecord
{
	my ($this, $inputFile) = @_;
	#Strip inputFile parameter of any unnecessary characters.
	chomp $inputFile;

	#Count number of lines in file and subtract one to get number of students.
	my $count = `wc -l < $inputFile`;
	chomp($count);
	$this->{studentNum} = $count - 1;

	#Create file object, call it FILE.
	open(FILE, "<", "$inputFile") || die "Error in : $!";
	#Store each line of the file in an array.
	my @array = <FILE>;
	#Close file for good measure.
	close FILE;

	#Disregard first element of the array. (This is the line in the file that
    #says CLA OLA Quiz ... etc.)
	splice @array, $0, 1;

	#Start filling in the roster and initializing Student objects.
	for(my $i = 0; $i < $this->{studentNum}; $i++)
	{
		#Create an array of substrings for convenience.
		my @wordArray = split(/\s+/, $array[$i]);
		#Create and initialize new Student type object.
		my $newStudent = Student->new($wordArray[0], $wordArray[1],
			                          $wordArray[2], $wordArray[3],
			                          $wordArray[4], $wordArray[5],
			                          $wordArray[6]);
		#Add new Student type object to the roster, calculate their total
		#grade, and determine their final letter grade.
		$this->{studentArray}->[$i] = $newStudent;
		$this->{studentArray}->[$i]->calculateTotal();
		$this->{studentArray}->[$i]->determineLetterGrade();
	}
	return;
 }

#******************************************************************************
#This subroutine prints the information for a selected student contained in the
#roster.
sub printStudentInformation
{
	my ($this, $cNumber) = @_;

	#Search through roster to find desired student.
	for(my $i = 0; $i < $this->{studentNum}; $i++)
	{
		#Make two variables for comparison.
		my $cmpr1 = substr($this->{studentArray}->[$i]->getID(), 1);
		my $cmpr2 = substr($cNumber, 1);
		#Based on truth value of comparison, print appropriate information.
		if($cmpr1-1000 == $cmpr2-1000)
		{
			print "Here is the information for student $cNumber";
			print "\nID          CLA        OLA        Quiz        Exam";
			print "        FinalExam        Total        FinalGrade\n";
			print "-"x98;
			print "\n";
			print $this->{studentArray}->[$i]->getID();
			$this->{studentArray}->[$i]->displayScores();
			printf '%-16d', $this->{studentArray}->[$i]->getTotal();
			print $this->{studentArray}->[$i]->getLetterGrade();
			print "\n\n";
		}
	}

	return;
}

#******************************************************************************
#This subroutine prints the entire roster (ie all students and their associated
#information).
sub printRoster
{
	my ($this) = @_;

	print "Here is the entire roster:\n";
	print "ID          CLA        OLA        Quiz        Exam";
	print "        FinalExam        Total        FinalGrade\n";
	print "-"x98;
	print "\n";

	#Print whole roster.
	for(my $i = 0; $i < $this->{studentNum}; $i++)
	{
		print $this->{studentArray}->[$i]->getID();
		$this->{studentArray}->[$i]->displayScores();
		printf '%-16d', $this->{studentArray}->[$i]->getTotal();
		print $this->{studentArray}->[$i]->getLetterGrade();
		print "\n\n";
	}
	return;
}

#Return true
1;