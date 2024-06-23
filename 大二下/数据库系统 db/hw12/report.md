# DB exercise

3200105872 庄毅非

##### 17.6 Consider the precedence graph of Figure 17.16. Is the corresponding schedule conflict serializable? Explain your answer.

Answer: 

​	It can be serializable, since there are no cycle in precedence graph.



##### 17.7 What is a cascadeless schedule? Why is cascadelessness of schedules desirable? Are there any circumstances under which it would be desirable to allow noncascadeless schedules? Explain your answer.

Answer: 

​	A cascadeless schedule means for each pair transaction T1 and T2, if  T2 read item which was previous written by T1, then T1's `commit `operation must happen before T2's read operation.

​	Cascadeless schedule is often desirable since one transaction's failure won't lead to other transaction's failure. 

​	If in a system, transaction's failure is rarely, then we can consider use noncascadeless schedules.

 