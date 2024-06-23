import * as React from 'react';
import Avatar from '@mui/material/Avatar';
import Button from '@mui/material/Button';
import CssBaseline from '@mui/material/CssBaseline';
import TextField from '@mui/material/TextField';
import Paper from '@mui/material/Paper';
import Box from '@mui/material/Box';
import Grid from '@mui/material/Grid';
import Typography from '@mui/material/Typography';
import { createTheme, ThemeProvider } from '@mui/material/styles';
import Copyright from '../components/CopyRight';
import axios from 'axios';
import { Alert } from '@mui/material';
import Router from 'next/router';
import { useDispatch } from 'react-redux';
import { setUserName as higherSetUserName } from '../redux/username.slice';
import { setUserID as higherSetUserID } from '../redux/userid.slice';
const theme = createTheme();

const checkPhone = (phoneNumberValue) => {
  const regex = /^[1][0-9]{10}$/;
  return regex.test(phoneNumberValue);
};

const login = (userNameValue, passWordValue) => {
  return axios({
    url: 'http://localhost:9000/user/login',
    method: 'POST',
    data: {
      userName: userNameValue,
      password: passWordValue,
    },
    withCredentials: true,
    headers: {
      Accept: 'application/json',
      'Content-Type': 'application/json',
    },
  });
};
const register = (phoneNumberValue, userNameValue, passWordValue) => {
  return axios({
    url: 'http://localhost:9000/user/register',
    method: 'POST',
    data: {
      phoneNumber: phoneNumberValue,
      userName: userNameValue,
      password: passWordValue,
    },
    withCredentials: true,
    headers: {
      Accept: 'application/json',
      'Content-Type': 'application/json',
    },
  });
};
export default function SignInSide() {
  const dispatch = useDispatch();
  const [status, setStatus] = React.useState('login');

  const phoneNumber = React.useRef('');
  const userName = React.useRef('');
  const password = React.useRef('');
  const [phoneAlert, setPhoneAlert] = React.useState(false);
  const [userNameAlert, setUserNameAlert] = React.useState(false);
  const [passwordAlert, setPassWordAlert] = React.useState(false);
  const [errMsgAlert, setErrMsgAlert] = React.useState('');
  // 电话不能通过正则
  const [phoneNotMatch, setPhoneNotMatch] = React.useState(false);
  // 用户名太短
  const [userNameTooShort, setUserNameTooShort] = React.useState(false);
  // 密码太短
  const [passwordTooShort, setPassWordTooShort] = React.useState(false);

  const setUserName = (username) => {
    dispatch(higherSetUserName(username));
  };
  const setUserID = (userid) => {
    dispatch(higherSetUserID(userid));
  };
  const handleSubmit = async (event) => {
    event.preventDefault();
    const phoneNumberValue = phoneNumber.current?.value;
    const userNameValue = userName.current?.value;
    const passWordValue = password.current?.value;
    // 检测电话是否太短
    if (!passWordValue || passWordValue.length < 6) {
      setPassWordAlert(true);
      setTimeout(() => {
        setPassWordAlert(false);
      }, 3000);
      return;
    }
    if (
      status === 'register' &&
      (!phoneNumberValue || !checkPhone(phoneNumberValue))
    ) {
      // 检测电话是否符合正则
      setPhoneAlert(true);
      setTimeout(() => {
        setPhoneAlert(false);
      }, 3000);
      return;
    }
    // 检测用户名是否太短
    if (!userNameValue || userNameValue.length < 6) {
      setUserNameAlert(true);
      setTimeout(() => {
        setUserNameAlert(false);
      }, 3000);
      console.log('username too short');
      return;
    }
    // 通过检测
    // 登陆或者注册
    await (status === 'login'
      ? login(userNameValue, passWordValue)
      : register(phoneNumberValue, userNameValue, passWordValue)
    )
      .then((res) => {
        console.log('成功');
        if (status === 'login') {
          setUserName(userNameValue);
          setUserID(res.data.userid);
          Router.push('/dashboard');
        } else {
          setStatus('login');
        }
      })
      .catch((err) => {
        setErrMsgAlert(
          err.response?.data.error ? err.response?.data.error : '登陆失败',
        );
        setTimeout(() => {
          setErrMsgAlert('');
        }, 5000);
        console.log(err);
      });
    //* 处理错误代码等
  };
  return (
    <ThemeProvider theme={theme}>
      {passwordAlert ? <Alert severity='error'>密码不足6位!</Alert> : <></>}
      {userNameAlert ? <Alert severity='error'>用户名不足6位!</Alert> : <></>}
      {phoneAlert ? <Alert severity='error'>手机号错误!</Alert> : <></>}
      {!passwordAlert && !userNameAlert && !phoneAlert && errMsgAlert === '' ? (
        <></>
      ) : (
        <Alert severity='error'>{errMsgAlert}</Alert>
      )}
      <Grid
        container
        component='main'
        sx={{ height: '100vh' }}
        gridTemplateColumns='1fr 1fr'>
        <CssBaseline />
        <Grid
          item
          xs={false}
          sm={4}
          md={7}
          sx={{
            backgroundImage:
              'url(https://images.unsplash.com/photo-1554995207-c18c203602cb?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=2070&q=80)',
            backgroundRepeat: 'no-repeat',
            backgroundColor: (t) =>
              t.palette.mode === 'light'
                ? t.palette.grey[50]
                : t.palette.grey[900],
            backgroundSize: 'cover',
            backgroundPosition: 'center',
          }}
        />
        <Grid item xs={12} sm={8} md={5} component={Paper} elevation={6} square>
          <Box
            sx={{
              my: 8,
              mx: 4,
              display: 'flex',
              flexDirection: 'column',
              alignItems: 'center',
            }}>
            <Avatar sx={{ m: 1, bgcolor: 'secondary.main' }}></Avatar>
            <Typography component='h1' variant='h5'>
              {status == 'login' ? '登陆' : '注册'}
            </Typography>
            <Box
              component='form'
              noValidate
              onSubmit={handleSubmit}
              sx={{ mt: 1 }}
              fullWidth>
              {status == 'register' ? (
                <TextField
                  margin='normal'
                  required
                  fullWidth
                  id='phoneNumber'
                  label='手机号'
                  name='phoneNumber'
                  autoComplete='phoneNumber'
                  autoFocus
                  inputRef={phoneNumber}
                  error={phoneNotMatch}
                  helperText={phoneNotMatch ? '手机号错误' : ''}
                  onChange={(e) => {
                    if (checkPhone(e.target.value)) {
                      setPhoneNotMatch(false);
                    } else {
                      setPhoneNotMatch(true);
                    }
                  }}
                />
              ) : (
                <React.Fragment></React.Fragment>
              )}
              <TextField
                margin='normal'
                required
                fullWidth
                id='username'
                label='用户名'
                name='username'
                autoComplete='username'
                autoFocus
                inputRef={userName}
                error={userNameTooShort}
                helperText={userNameTooShort ? '用户名不足6位' : ''}
                onChange={(e) => {
                  if (e.target.value.length < 6) {
                    setUserNameTooShort(true);
                  } else {
                    setUserNameTooShort(false);
                  }
                }}
              />
              <TextField
                margin='normal'
                required
                fullWidth
                name='password'
                label='密码'
                type='password'
                id='password'
                autoComplete='current-password'
                inputRef={password}
                error={passwordTooShort}
                helperText={passwordTooShort ? '密码不足6位' : ''}
                onChange={(e) => {
                  if (e.target.value.length < 6) {
                    setPassWordTooShort(true);
                  } else {
                    setPassWordTooShort(false);
                  }
                }}
              />

              <Button
                type='submit'
                fullWidth
                variant='contained'
                sx={{ mt: 3, mb: 2 }}>
                {status === 'login' ? '登陆' : '注册'}
              </Button>
              <Grid container>
                <Grid item>
                  <Button
                    onClick={() =>
                      setStatus(status === 'login' ? 'register' : 'login')
                    }
                    variant='body2'
                    sx={{
                      backgroundColor: '#03a9f4',
                    }}>
                    注册
                  </Button>
                </Grid>
              </Grid>
              <Copyright sx={{ mt: 5 }} />
            </Box>
          </Box>
        </Grid>
      </Grid>
    </ThemeProvider>
  );
}
