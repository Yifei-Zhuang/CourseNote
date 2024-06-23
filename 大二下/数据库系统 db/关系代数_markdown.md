\\关系代数\\
$\sigma_{sno = 1}(Student)$\\
$\sigma_{sno = 1 \wedge sage >18 \vee ssex="F"}(Student)$\\

$\Pi_{sno,cno}(Student)$
\\
$Student \Join SC$
\\
$Student \underset{Student.Sno=SC.Sno}\Join  SC$
\\
$R \cup S$
\\
$R \cap S$
\\
$\Pi_{Sname}(\Pi_{sno}(\sigma_{Cpno='5'}(Course)\Join SC)\Join \Pi_{Sno,Sname}(Student))$$\sigma_{sno = 1}(Student)$\\
$\sigma_{sno = 1 \wedge sage >18 \vee ssex="F"}(Student)$\\

$\Pi_{sno,cno}(Student)$
\\
$Student \Join SC$
\\
$Student \underset{Student.Sno=SC.Sno}\Join  SC$
\\
$R \cup S$
\\
$R \cap S$
\\
$\Pi_{Sname}(\Pi_{sno}(\sigma_{Cpno='5'}(Course)\Join SC)\Join \Pi_{Sno,Sname}(Student))$