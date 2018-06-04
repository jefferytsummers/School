#### Author:      Ryan Florida
#### Program:     OLA2
#### File:        Student.pm
#### Date:        April 10, 2017
#### Description: This file is part of the second open lab assignment, which
####              includes ola2.pl, Student.pm, and Roster.pm. This file gives
####              the full definition of the class Student.

package Student;

#Constructor.
sub new{
	$class = shift;
	$this = {
		#Member data to be initialized when object is instantiated.
		id          => shift,
		CLA         => shift,
		OLA         => shift,
		Quiz        => shift,
		Exam        => shift,
		FinalExam   => shift,
	};

	#Member data to be filled in appropriately later.
	$this->{total} = 0;
	$this->{letterGrade} = '';

	#Give Student class properties.
	bless $this, $class;

	return $this;
}

#Accessors
#******************************************************************************
#Return id to caller.
sub getID{
	my ($this) = @_;
	return $this->{id};
}

#******************************************************************************
#Return total to caller.
sub getTotal{
	my ($this) = @_;

	return $this->{total};
}

#******************************************************************************
#Return letterGrade to caller.
sub getLetterGrade{
	my ($this) = @_;

	return $this->{letterGrade};
}


#******************************************************************************
#Display nicely formatted score information for user.
sub displayScores{
	my ($this) = @_;
	print "    ";
	printf '%-11d', $this->{CLA};
	printf '%-12d', $this->{OLA};
	printf '%-12d', $this->{Quiz};
	printf '%-14d', $this->{Exam};
	printf '%-15d', $this->{FinalExam};
	return;
}

#Mutators
#******************************************************************************
#Calculate total grade based upon all other grades.
sub calculateTotal{
	my ($this) = @_;
	#Sum all score information and assign it to total data member.
	$this->{total} = $this->{CLA} + $this->{OLA} + $this->{Quiz}
	                   + $this->{Exam} + $this->{FinalExam};

	return $this->{total};
}

#******************************************************************************
#Determine which letter grade the student shall recieve based upon their total
#grade.
sub determineLetterGrade{
	my ($this) = @_;
	#Grade assignment based on OLA description.
	if(($this->{total}) < 60){
		$this->{letterGrade} = 'F';
	}
	elsif(($this->{total}) < 63){
		$this->{letterGrade} = 'D-';
	}
	elsif(($this->{total})< 67){
		$this->{letterGrade} = 'D';
	}
	elsif(($this->{total}) < 70){
		$this->{letterGrade} = 'D+';
	}
	elsif(($this->{total}) < 73){
		$this->{letterGrade} = 'C-';
	}
	elsif(($this->{total}) < 77){
		$this->{letterGrade} = 'C';
	}
	elsif(($this->{total}) < 80){
		$this->{letterGrade} = 'C+';
	}
	elsif(($this->{total}) < 83){
		$this->{letterGrade} = 'B-';
	}
	elsif(($this->{total}) < 87){
		$this->{letterGrade} = 'B';
	}
	elsif(($this->{total}) < 90){
		$this->{letterGrade} = 'B+';
	}
	else{
		($this->{letterGrade}) = 'A';
	}

	return $this->{letterGrade};
}

#Return true;
1;