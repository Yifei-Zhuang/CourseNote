# Design and coding

##### 软件需求工程 Fissure组 milestone 4

组员： 庄毅非、李予谦、刘奕骁、应凌凯、何迪

## 1. 引言

### 1.1 编写目的

​	系统设计计划主要为使软件产品和软件项目满足规定的软件规格要求而确定软件系统的体系结构、组成部分、数据组织、模块、内外部接口。主要任务有:

​	(1)建立软件产品和软件项目目标系统的总体结构;

​	(2)总体设计;
​	(3)接口设计;
​	(4)运行设计;

​	(5)系统数据结构设计;

​	(6)系统出错处理设计。

### 1.2 项目简介

​	我们所要开发的开源项目分析平台面向的用户主要是开源项目管理者。通过使用我们开发的平台，开源项目管理者能够方便的管控项目的开发进程。

​	开源项目管理者可以使用我们的平台对软件开发的贡献者进行分析，从中将其归类为核心贡献者和其他贡献者，通过有效的措施增加贡献者的留存率，发现新的核心贡献者;可以可视化展示参与开发的人员的所属公司，方便管理者和对应的公司进行合作，更好推进项目发展;可以对项目的代码质量进行高效评估，确保项目代码质量。可以对项目的issue、pullrequest进行分析，从中挖掘出用户(主要是开发者)对软件所提出的需求，把我软件开发方向和里程碑。通过上述措施，更好地推进项目开发进程，确保开源项目长久运行下去。

## 2. 系统环境

### 2.1 运行环境

#### 2.1.1 软件层面

​	开源项目分析平台 DoubleC 以网页的形式呈现数据，建议用户使用chrome进行浏览。

​	项目服务端运行在云服务器上，数据库使用mongodb，这是一种新兴的nosql数据库，能够支持数据的快速存取和修改操作。

#### 2.1.2 硬件层面

​	硬件层面对于所使用的服务器有以下要求:

	 - CPU:主频大于 2.0GHz
	 - 内存:大于等于 2GB
	 - 硬盘:硬盘容量大于 200GB、硬盘转速大于等于 5400 转/分钟 
	 - 网卡:百兆网卡
	 - 网线:具有良好的数据传输能力即可 
	 - 键盘:可以满足正常使用即可 
	 - 鼠标:可以满足正常使用即可 
	 - 显示器:可以满足正常使用即可

### 2.2 测试环境

​	我们计划对win10，win11，macos和ubuntu平台进行测试

### 2.3 系统模块设计

1. 用户管理模块
   1. 主要包括用户注册，登录，修改信息操作
2. 数据导入模块
   1. 爬取开源项目（来自github）的commit信息
   2. 爬取开源项目（来自github）的issue信息
   3. 爬取开源项目（来自github）的pull信息
   4. 爬取开源项目（来自github）的contributor信息
   5. 爬取开源项目（来自github）的comment信息
3. 数据显示模块
   1. 显示仓库总体信息
   2. 以图表的形式可视化显示commit频率按照每月，每年的变化
   3. 以图表的形式可视化显示issue create/update/close频率按照每月，每年的变化
   4. 以图表的形式可视化显示pull create/update/close频率按照每月，每年的变化
   5. 以图表的形式可视化显示puller、issuer、commiter数量随时间变化的情况，**反映社区热度**
   6. 用多种图表反映issue从提出到第一次响应所需要的时间的变化（包括最短时间，前1/4时间，前1/2时间，前3/4时间和最长时间），**反映社区热度**
   7. 用多种图表反映issue从提出到close所需要的时间的变化（包括最短时间，前1/4时间，前1/2时间，前3/4时间和最长时间），**反映社区热度**
   8. 分析并显示不同时期issue和pull中主要讨论的话题
   9. 实现两个仓库的对比
4. 数据分析模块
   1. 实现对上述数据显示模块中可视化所需数据的快速计算和返回

#### 2.3.2 应用架构

​	我们小组计划使用普遍使用的B/S架构进行开发

### 2.4 数据处理

#### 2.4.1 数据存储

​	项目产品使用标准 Mongodb 数据库系统作为引擎，按照数据产生、转换和存储的策略， 通过将数据导入数据库的方式进行数据的存储操作。

#### 2.4.2 数据安全

​	我们对服务器mongo的访问ip白名单，数据库访问用户名、密码（使用pwgen生成，保障安全性）和持有的权限进行了严格的限制，确保小组之外的成员无法访问数据库。

### 2.4.3 数据库设计

​	数据表总览。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/R4XI3S.png)

​	各个数据表的定义，由于内容较多，我们放到了附录中进行展示。

## 3. 系统实现

//TODO







## 4. 附录

### 4.1 数据表定义

#### 4.1.1 commit表定义

​	存储每个commit的基本信息。

```js
const CommitSchema = new mongoose.Schema({
  sha: {
    type: String,
    required: [true, 'must provide sha'], //must have the property
  },
  url: {
    type: String,
    required: [true, 'must provide url'],
  },
  author_id: {
    type: Number,
  },
  author_name: {
    type: String,
  },
  author_email: {
    type: String,
  },
  updated_at: {
    type: String,
  },
  message: {
    type: String,
  },
  repos_id: {
    type: String,
    required: [true, 'must provide repos_id'],
  },
  // 以下为冗余字段，仅供查询使用
  repo_owner: {
    type: String,
    required: [true, 'must provide repo_owner'],
  },
  repo_name: {
    type: String,
    required: [true, 'must provide repo_name'],
  },
});
```

#### 4.1.2 commiteryearcache表定义

​	缓存表，存储每年的commit总数的变化情况。

```js
const CommitYearCacheSchema = new mongoose.Schema({
  commit_year_frequency: {
    type: Object,
    required: [true, 'must provide commit_year_frequency'],
  },
  // 以下为冗余字段，仅供查询使用
  repo_owner: {
    type: String,
    required: [true, 'must provide repo_owner'],
  },
  repo_name: {
    type: String,
    required: [true, 'must provide repo_name'],
  },
});

```

#### 4.1.3 commitMonthCache表定义

​	缓存表，存储每月的commit频率的变化情况。

```js
const CommitMonthCacheSchema = new mongoose.Schema({
  commit_month_frequency: {
    type: Object,
    required: [true, 'must provide commit_month_frequency'],
  },
  // 以下为冗余字段，仅供查询使用
  repo_owner: {
    type: String,
    required: [true, 'must provide repo_owner'],
  },
  repo_name: {
    type: String,
    required: [true, 'must provide repo_name'],
  },
});

```

#### 4.1.4 commiter表定义

​	缓存表，存储每月的commiter数量的变化情况。

```js
const CommiterCacheSchema = new mongoose.Schema({
  commiter_count: {
    type: Object,
    required: [true, 'must provide commiter_count'],
  },
  // 以下为冗余字段，仅供查询使用
  repo_owner: {
    type: String,
    required: [true, 'must provide repo_owner'],
  },
  repo_name: {
    type: String,
    required: [true, 'must provide repo_name'],
  },
});
```

#### 4.1.5 githubuser表定义

​	存储github用户信息，用来分析公司贡献。

```js
const GithubUserSchema = new mongoose.Schema({
  login: {
    type: String,
    required: [true, 'must provide loginname'],
  },
  company: {
    type: String,
  },
});
```

#### 4.1.6 issueComment表定义

​	存储了对issue进行评论（如果有）的第一条非机器人评论，用来分析issue的第一次得到响应时间。

```js
const IssueCommentSchema = new mongoose.Schema({
  url: {
    type: String,
    required: [true, 'must provide url'],
  },
  created_at: {
    type: String,
    required: [true, 'must provide created_at'],
  },
  issue_id: {
    type: Number,
  },
  body: {
    type: String,
  },
  issue_number: {
    type: Number,
  },
  valid: {
    type: Boolean,
    default: true,
  }, // 以下为冗余字段，仅供查询使用
  repo_owner: {
    type: String,
    required: [true, 'must provide repo_owner'],
  },
  repo_name: {
    type: String,
    required: [true, 'must provide repo_name'],
  },
});
```

#### 4.1.7 issueCommentCache表定义

​	缓存表，存储已经计算出来的过去月份的平均响应时间，避免重复计算。

```js
const IssueCommentCacheSchema = new mongoose.Schema({
  month: {
    type: String,
    required: [true, 'must provide month'],
  },
  value: {
    type: Object,
    require: [true, 'must provide value'],
  },
  // 以下为冗余字段，仅供查询使用
  repo_owner: {
    type: String,
    required: [true, 'must provide repo_owner'],
  },
  repo_name: {
    type: String,
    required: [true, 'must provide repo_name'],
  },
});
```

#### 4.1.8 issueMonthCloseCache表

​	缓存表，存储已经计算出来的过去月份的close数量，避免重复计算。

```js
const IssueMonthCloseCacheSchema = new mongoose.Schema({
    issue_month_close_frequency: {
        type: Object,
        required: [true, 'must provide issue_month_close_frequency'],
    },
    // 以下为冗余字段，仅供查询使用
    repo_owner: {
        type: String,
        required: [true, 'must provide repo_owner'],
    },
    repo_name: {
        type: String,
        required: [true, 'must provide repo_name'],
    },
});


```

### 4.1.9 issueMonthCreateCache

​	缓存表，存储已经计算出来的过去月份的create数量，避免重复计算。

```js
const IssueMonthCreateCacheSchema = new mongoose.Schema({
    issue_month_create_frequency: {
        type: Object,
        required: [true, 'must provide issue_month_create_frequency'],
    },
    // 以下为冗余字段，仅供查询使用
    repo_owner: {
        type: String,
        required: [true, 'must provide repo_owner'],
    },
    repo_name: {
        type: String,
        required: [true, 'must provide repo_name'],
    },
});

```

### 4.1.10 issueMonthUpdateCache

​	缓存表，存储已经计算出来的过去月份的update数量，避免重复计算。

```js
const IssueMonthUpdateCacheSchema = new mongoose.Schema({
    issue_month_update_frequency: {
        type: Object,
        required: [true, 'must provide issue_month_update_frequency'],
    },
    // 以下为冗余字段，仅供查询使用
    repo_owner: {
        type: String,
        required: [true, 'must provide repo_owner'],
    },
    repo_name: {
        type: String,
        required: [true, 'must provide repo_name'],
    },
});
```

#### 4.1.11 issueYearCloseCache表

​	缓存表，存储已经计算出来的过去年份的close数量，避免重复计算。

```js
const IssueYearCloseCacheSchema = new mongoose.Schema({
    issue_year_close_frequency: {
        type: Object,
        required: [true, 'must provide issue_year_close_frequency'],
    },
    // 以下为冗余字段，仅供查询使用
    repo_owner: {
        type: String,
        required: [true, 'must provide repo_owner'],
    },
    repo_name: {
        type: String,
        required: [true, 'must provide repo_name'],
    },
});
```

### 4.1.12 issueYearCreateCache表

​	缓存表，存储已经计算出来的过去月份的create数量，避免重复计算。

```js
const IssueYearCreateCacheSchema = new mongoose.Schema({
    issue_year_create_frequency: {
        type: Object,
        required: [true, 'must provide issue_year_create_frequency'],
    },
    // 以下为冗余字段，仅供查询使用
    repo_owner: {
        type: String,
        required: [true, 'must provide repo_owner'],
    },
    repo_name: {
        type: String,
        required: [true, 'must provide repo_name'],
    },
});

```

### 4.1.13 issueMonthUpdateCache表

​	缓存表，存储已经计算出来的过去年份的update数量，避免重复计算。

```js
const IssueYearUpdateCacheSchema = new mongoose.Schema({
    issue_year_update_frequency: {
        type: Object,
        required: [true, 'must provide issue_year_update_frequency'],
    },
    // 以下为冗余字段，仅供查询使用
    repo_owner: {
        type: String,
        required: [true, 'must provide repo_owner'],
    },
    repo_name: {
        type: String,
        required: [true, 'must provide repo_name'],
    },
});
```

#### 4.1.14 issue表定义

```js
const IssueSchema = new mongoose.Schema({
  id: {
    type: Number,
    required: [true, 'must provide id'], //must have the property
  },
  number: {
    type: Number,
  },
  url: {
    type: String,
  },
  title: {
    type: String,
  },
  state: {
    type: String,
  },
  is_locked: {
    type: Boolean,
  },
  body: {
    type: String,
  },
  created_at: {
    type: String,
    required: [true, 'must provide created_at'],
  },
  updated_at: {
    type: String,
    required: [true, 'must provide updated_at'],
  },
  closed_at: {
    type: String,
  },
  repos_id: {
    type: Number,
  },
  user_id: {
    type: Number,
  },
  user_name: {
    type: String,
  },
  comment_count: {
    type: Number,
    require: [true, 'must provide comment_count'],
  },
  labels: {
    type: [String],
  },
  // 以下为冗余字段，仅供查询使用
  repo_owner: {
    type: String,
    required: [true, 'must provide repo_owner'],
  },
  repo_name: {
    type: String,
    required: [true, 'must provide repo_name'],
  },
});

```

#### 4.1.15 issueCache表定义

​	缓存表，存储了过去每月的issuer数量变化

```js
const IssuerCacheSchema = new mongoose.Schema({
    issuer_count: {
        type: Object,
        required: [true, 'must provide issuer_count'],
    },
    // 以下为冗余字段，仅供查询使用
    repo_owner: {
        type: String,
        required: [true, 'must provide repo_owner'],
    },
    repo_name: {
        type: String,
        required: [true, 'must provide repo_name'],
    },
});

```

#### 4.1.16 pullMonthCloseCache表

​	缓存表，存储已经计算出来的过去月份的close数量，避免重复计算。

```js
const PullMonthCloseCacheSchema = new mongoose.Schema({
    pull_month_close_frequency: {
        type: Object,
        required: [true, 'must provide pull_month_close_frequency'],
    },
    // 以下为冗余字段，仅供查询使用
    repo_owner: {
        type: String,
        required: [true, 'must provide repo_owner'],
    },
    repo_name: {
        type: String,
        required: [true, 'must provide repo_name'],
    },
});


```

### 4.1.13 PullMonthCreateCache

​	缓存表，存储已经计算出来的过去月份的create数量，避免重复计算。

```js
const PullMonthCreateCacheSchema = new mongoose.Schema({
    pull_month_create_frequency: {
        type: Object,
        required: [true, 'must provide pull_month_create_frequency'],
    },
    // 以下为冗余字段，仅供查询使用
    repo_owner: {
        type: String,
        required: [true, 'must provide repo_owner'],
    },
    repo_name: {
        type: String,
        required: [true, 'must provide repo_name'],
    },
});

```

### 4.1.14 pullMonthUpdateCache

​	缓存表，存储已经计算出来的过去月份的update数量，避免重复计算。

```js
const PullMonthUpdateCacheSchema = new mongoose.Schema({
    pull_month_update_frequency: {
        type: Object,
        required: [true, 'must provide     pull_month_update_frequency'],
    },
    // 以下为冗余字段，仅供查询使用
    repo_owner: {
        type: String,
        required: [true, 'must provide repo_owner'],
    },
    repo_name: {
        type: String,
        required: [true, 'must provide repo_name'],
    },
});
```

#### 4.1.15 pullYearCloseCache表

​	缓存表，存储已经计算出来的过去年份的close数量，避免重复计算。

```js
const PullYearCloseCacheSchema = new mongoose.Schema({
    pull_year_close_frequency: {
        type: Object,
        required: [true, 'must provide pull_year_close_frequency'],
    },
    // 以下为冗余字段，仅供查询使用
    repo_owner: {
        type: String,
        required: [true, 'must provide repo_owner'],
    },
    repo_name: {
        type: String,
        required: [true, 'must provide repo_name'],
    },
});
```

### 4.1.16 pullYearCreateCache表

​	缓存表，存储已经计算出来的过去月份的create数量，避免重复计算。

```js
const PullYearCreateCacheSchema = new mongoose.Schema({
    pull_year_create_frequency: {
        type: Object,
        required: [true, 'must provide pull_year_create_frequency'],
    },
    // 以下为冗余字段，仅供查询使用
    repo_owner: {
        type: String,
        required: [true, 'must provide repo_owner'],
    },
    repo_name: {
        type: String,
        required: [true, 'must provide repo_name'],
    },
});

```

### 4.1.17 pullMonthUpdateCache表

​	缓存表，存储已经计算出来的过去年份的update数量，避免重复计算。

```js
const PullYearUpdateCacheSchema = new mongoose.Schema({
    pull_year_update_frequency: {
        type: Object,
        required: [true, 'must provide pull_year_update_frequency'],
    },
    // 以下为冗余字段，仅供查询使用
    repo_owner: {
        type: String,
        required: [true, 'must provide repo_owner'],
    },
    repo_name: {
        type: String,
        required: [true, 'must provide repo_name'],
    },
});
```

#### 4.1.18 pull表定义

```js
const PullSchema = new mongoose.Schema({
  id: {
    type: Number,
    required: [true, 'must provide id'], //must have the property
  },
  url: {
    type: String,
    required: [true, 'must provide url'],
  },
  number: {
    type: Number,
    required: [true, 'must provide number'],
  },
  state: {
    type: String,
    required: [true, 'must provide state'],
  },
  title: {
    type: String,
    required: [true, 'must provide title'],
  },
  isLocked: {
    type: Boolean,
    required: [true, 'must provide isLocked'],
  },
  body: {
    type: String,
    required: [true, 'must provide body'],
  },
  created_at: {
    type: String,
    required: [true, 'must provide created_at'],
  },
  updated_at: {
    type: String,
    required: [true, 'must provide updated_at'],
  },
  closed_at: {
    type: String,
  },
  is_merged: {
    type: Boolean,
    required: [true, 'must provide is_merged'],
  },
  repos_id: {
    type: Number,
    required: [`true,'must provide repo's id`],
  },
  user_id: {
    type: String,
  },
  labels: {
    type: [String],
  },
  // 以下为冗余字段，仅供查询使用
  repo_owner: {
    type: String,
    required: [true, 'must provide repo_owner'],
  },
  repo_name: {
    type: String,
    required: [true, 'must provide repo_name'],
  },
});

```

#### 4.1.15 issueCache表定义

​	缓存表，存储了过去每月的issuer数量变化

```js
const PullerCacheSchema = new mongoose.Schema({
    puller_count: {
        type: Object,
        required: [true, 'must provide puller_count'],
    },
    // 以下为冗余字段，仅供查询使用
    repo_owner: {
        type: String,
        required: [true, 'must provide repo_owner'],
    },
    repo_name: {
        type: String,
        required: [true, 'must provide repo_name'],
    },
});

```

#### 4.1.16 repo

​	描述仓库的基本信息。

```js
const Repo = new mongoose.Schema({
  name: {
    type: String,
    required: [true, 'must provide name'], //must have the property
  },
  owner: {
    type: String,
    required: [true, 'must provide owner'],
  },
  uploader: {
    type: String,
    required: [true, 'must provide uploader'],
  },
  forks: {
    type: Number,
    required: [true, 'must provide forks'],
  },
  stars: {
    type: Number,
    required: [true, 'must provide stars'],
  },
  open_issues: {
    type: Number,
    required: [true, 'must provide open_issues'],
  },
  commit_frequency: {
    type: Object,
    required: [true, 'must provide commit_frequency'],
  },
  issue_frequency: {
    type: Object,
    required: [true, 'must provide issue_frequency'],
  },
  contributors: {
    type: [Object],
    required: [true, 'must provide contributors'],
  },
  timeline: {
    type: Object,
  },
  language: {
    type: Object,
  },
});

```

#### 4.1.17 user表

​	描述系统注册用户的信息

```js
const User = new mongoose.Schema({
    username: {
        type: String,
        required: [true, 'Please provide name'],
        maxlength: [20, 'Password should be less than 20 characters'],
        minlength: [3, 'Password should be more than 3 characters'],
        trim: true,
    },
    email: {
        type: String,
        required: [true, 'Please provide email'],
        match: [
            /^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/ ,
            'Please provide a valid email',
        ],
        unique: [true, 'The email is already used!'],
    },
    password: {
        type: String,
        required: [true, 'Please provide password'],
        minlength: [6, 'Password should be more than 6 characters'],
    }

})
```



















































