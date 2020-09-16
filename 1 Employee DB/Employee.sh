#Return Employee ID For New Employees
CurrentNumber()
{
    	local eno=1     
    	f=0	#Flag
	for j in `cut -f1 Employee.txt`
	do 
		f=1
	done
	if [ $f = 1 ]
            then
			#Return Next Employee ID
                        eno=`expr $j + 1`
            else
			#Return 1 For New Employee
                        eno=1
            fi
            echo $eno
}

Insert()
{
	clear
	eno=$1	#Parameter Passed (Empployee ID)
	echo "Employee Id : $eno"
	echo "Employee Name : \c"
	read ename;
	echo "Employee Designation : \c"
	read edes;
	echo "Employee Department : \c"
	read edep;
	echo "Employee Basic Salary : \c"
	read ebs;
	#Add Data To File
	echo "$eno \t $ename \t\t $edes \t $edep \t $ebs">>Employee.txt
	echo "\n\n--------------------\nInserted Successfully\n--------------------"
}

Display()
{
            echo "______________________________________________________________"                       
            echo "                Employee Details "
            echo "______________________________________________________________"                       
            echo "______________________________________________________________"                       
            echo "#ENO \t ENAME \t\t EDESIG  EDEPT \t ESALARY"    
            cat Employee.txt   
            echo "______________________________________________________________"                       
}

Update()
{
	f=0		#Fla
	line_no=1	#Get Which Line To Update
	s="s"
	echo "Enter Employee Number : \c"
        read eno
	for j in `cut -f1 Employee.txt`
	do 
	if [ $j -eq $eno ]	#If Employee Found
	then
		f=1
        	echo "\n\n______________Enter New Record______________"
		echo "Employee Id : $eno"
		echo "Employee Name : \c"
		read ename;
		echo "Employee Designation : \c"
		read edes;
		echo "Employee Department : \c"
		read edep;
		echo "Employee Basic Salary : \c"
		read ebs;
		#Data To Be Added
		line=$(echo "$eno \t $ename \t\t $edes \t $edep \t $ebs")
		#Syntax: sed -i "Ns/.*/$Data/" FileName.txt                
		sed -i "$line_no$s/.*/$line/" Employee.txt     
                echo "\n\n---------------------Update Sucessfully---------------------"
	fi
	line_no=$((line_no+1))
	done
	if [ $f = 0 ]	#If Employee Not Found
        then
		echo "\n--------------------------------------------"
        	echo "               No Record Found              "
		echo "--------------------------------------------"
        fi	
}

Delete()
{
	f=0 #Flag
	echo "Enter Employee Number : \c"
        read no
	k=0	#Line Number
	d="d"
	for j in `cut -f1 Employee.txt`
	do 
	k=$((k+1))
	line_no="$k$d"
		if [ $j -eq $no ]
		then
			f=1
			#Syntx: sed -i $Nd FileName.txt
			sed -i $line_no Employee.txt			  
    		             echo "\n\n---------------------Delete Sucessfully---------------------"
		fi	
	done
	if [ $f = 0 ]	#If Employee Not Found
        then
		echo "\n--------------------------------------------"
        	echo "               No Record Found              "
		echo "--------------------------------------------"
        fi
}
GrossSalary()
{
	echo "Enter Employee Number Whose Gross Value Is TO Be Calculated : \c"
	read no;
	k=0	#Line Number Of Employee Whose GS Is To Be Calc.
	f=0	#Flag
	n=1	#Line Number Count To Get Data Of kth Line
	for j in `cut -f1 Employee.txt`
	do 
		k=$((k+1))		#Increment Line No
		if [ $j -eq $no ]	#Check If Data Avalable
		then
			f=1
			break	        
		fi	
	done
	if [ $f = 1 ]
	then
		while read line; do	#Read Data Line By Line
			if [ $n = $k ]	#When kth Line Reached
			then
				break
			fi
		n=$((n+1))
		done < Employee.txt
		#Print Data On kth Line
		echo "\n----------------------------------------"
		echo "Employee ID : \c"
		echo "$line" | awk '{print $1F}'
		echo "Employee Name : \c"
		echo "$line" | awk '{print $2F}'
		echo "Employee Designation : \c"
		echo "$line" | awk '{print $3F}'
		echo "Employee Department : \c"
		echo "$line" | awk '{print $4F}'
		echo "Employee Basic Salary : \c"
		echo "$line" | awk '{print $5F}'
		#Calculate Gross Salary
		bs=$(echo $line | cut -d ' ' -f5)
		da=`expr $(( bs * 2 / 5 ))`
		ra=`expr $bs / 5`
		res=`expr $bs + $da + $ra + 3000`
		echo "Gross Salary : $res"
		echo "\n----------------------------------------"
	fi
	if [ $f = 0 ]	#If Data Not Found
        then
		echo "\n--------------------------------------------"
        	echo "               No Record Found              "
		echo "--------------------------------------------"
        fi	
}

idno=$(CurrentNumber)
ins="y"
while true	#Run Till Programer Exits
do
echo "
------------------------------------
EMPLOYEE DATABASE MANAGEMENT MENU\n
1. Create List Of Record\n2. View All Records\n3. Insert A Record\n4. Delete A Record\n5. Modify A Record\n6. Gross Salary\n7. EXIT
------------------------------------
Enter Choice : \c"
read choice
case "$choice" in
#Insert N Number Of Records
1) while [ "$ins" = "y" -o "$ins" = "Y" ]
   do
   Insert $idno; idno=$((idno+1))
   echo "Do You Want To Continue ? (Y/y)  \c"
   read ins
   done
   ;;
#Display All Records
2) Display;;
#Insert A Record
3) Insert $idno; idno=$((idno+1));;
#Delete A Record
4) Delete;;
#Update A Record
5) Update;;
#Calculate Gross Salary
6) GrossSalary;;
#Exit Program
7) echo "\n\n--------------------\nProgram Completed\n--------------------"; exit;;
#Default : Invalid Choice
*) echo "**************INVALID CHOICE**************\n";;
esac
done

