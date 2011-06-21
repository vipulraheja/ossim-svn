#!/usr/bin/perl
use File::Copy;
$Base_Dir = "";
$header_index;
#$Headers_Dir = "";
@headers;
$cpp_index;
$c_index;
@cpp;
@c;

sub process_headers
{
	if (opendir(Input_Files, $Base_Dir . $_[0]))
	{
		foreach $name (sort readdir(Input_Files))
		{ 
			if (substr($name, length($name) - 2, length($name)) eq ".h")
			{
				@headers[$header_index] = $name;
				@headers_Path[$header_index] = $Base_Dir . $_[0] .  "/" . $name;
				$header_index = $header_index + 1;
			} elsif ($name ne "." && $name ne ".." && $name[0] ne '.')
			{
				process_headers($_[0] .  "/" . $name);
			}			
		} 
		closedir(Input_Files);
	}
}

sub process_cpp
{
	if (opendir(Input_Files, $Base_Dir . $_[0]))
	{
		foreach $name (sort readdir(Input_Files))
		{ 
			if (substr($name, length($name) - 4, length($name)) eq ".cpp" or
				substr($name, length($name) - 2, length($name)) eq ".c")
			{
				@cpp[$cpp_index] = $Base_Dir . $_[0] .  "/" . $name;
				$cpp_index = $cpp_index + 1;
			} elsif ($name ne "." && $name ne ".." && $name[0] ne '.')
			{
				process_cpp($_[0] .  "/" . $name);
			}			
		} 
		closedir(Input_Files);
	}
}

sub mod_headers
{
	# open each file in $headers_path
	open(HANDLE, @headers_Path[$_[0]]);
#	$outpath = $Headers_Dir . "/" . $headers[$_[0]];
	@raw_data=<HANDLE>;
	close(HANDLE);
	open(OUTHANDLE, ">@headers_Path[$_[0]]");
	
	foreach $line (@raw_data)
	{
		# search for lines starting with "#include"
		if ($line =~ m/#include/)
		{
			chop($line);
    		# compare .h file to all values in @headaers
			for ($j=1; $j < $header_index; $j++)
			{
				$position = index($line, @headers[$j]);

		 		if ($position ge 0)
		 		{
		 			if (substr($line, $position - 1, 1) eq '/' | substr($line, $position - 1, 1) eq '"' |
		 				substr($line, $position - 1, 1) eq '<')
		 			{
						 # if found change to "ossim/@headers[i]"
						$start = index($line, '"');
						if ($start eq -1)
						{
							$start = index($line, '<');
							$end = index($line, '>', $start + 1);
						} else
						{
							$end = index($line, '"', $start + 1);
						}
						$line = substr($line, 0, $start + 1) . "ossim/" . $headers[$j] . substr($line, $end, length($line));
						goto EXIT;
					}
		 		}
		 	}
		 	EXIT:
			print OUTHANDLE $line . "\n";
		} else
		{
			print OUTHANDLE $line;
		}
	}
	close(OUTHANDLE);
}

sub mod_body
{
print @cpp[$_[0]] . "\n";
	open(HANDLE, @cpp[$_[0]]);
	@raw_data=<HANDLE>;
	close(HANDLE);
	open(OUTHANDLE, ">@cpp[$_[0]]");
	
	foreach $line (@raw_data)
	{
		# search for lines starting with "#include"
		if ($line =~ m/#include/)
		{
			chop($line);
    		# compare .h file to all values in @headaers
			for ($j=1; $j < $header_index; $j++)
			{
				$position = index($line, @headers[$j]);

		 		if ($position ge 0)
		 		{
		 			if (substr($line, $position - 1, 1) eq '/' | substr($line, $position - 1, 1) eq '"' |
		 				substr($line, $position - 1, 1) eq '<')
		 			{		 		
						# if found change to "ossim/@headers[i]"
						
						$start = index($line, '"');
						if ($start eq -1)
						{
							$start = index($line, '<');
							$end = index($line, '>', $start + 1);
						} else
						{
							$end = index($line, '"', $start + 1);
						}
						$line = substr($line, 0, $start + 1) . "ossim/" . $headers[$j] . substr($line, $end, length($line));
						goto EXIT;
					}
		 		}
		 	}
		 	EXIT:
			print OUTHANDLE $line . "\n";
		} else
		{
			print OUTHANDLE $line;
		}
	}
	close(OUTHANDLE);

}

sub move_headers
{
#	mkdir "includes", 777
#	mkdir "includes/ossim", 777
	for ($j=1; $j < $header_index; $j++)
	{
		print $headers_Path[$j] . "\n";
		move($headers_Path[$j],"includes/ossim/");
	}
}

$header_index = 1;
process_headers("src/ossim_core");
for ($i=1; $i < $header_index; $i++)
{
	mod_headers($i);
}
$cpp_index = 1;
process_cpp("src");
for ($i=1; $i < $cpp_index; $i++)
{
	mod_body($i);
}
move_headers("src/ossim_core")