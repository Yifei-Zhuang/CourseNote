import { DashboardNavbar } from '../components/DashNavBar';
import { DashBoardWrapper } from './dashboard';
import SideBar from '../components/DashSideBar';
import {
  Box,
  CssBaseline,
  Divider,
  Grid,
  Typography,
  Container,
  CardHeader,
  CardContent,
  TextField,
  Button,
  Card,
} from '@mui/material';
import { AccountProfile } from '../components/AccountProfile';
import { useState } from 'react';
import axios from 'axios';
import { useSelector } from 'react-redux';
const EditPassword = (props) => {
  let userid = useSelector((state) => state.userID.value);
  const [password, setPassword] = useState('');
  const changePassword = () => {
    if (password?.length < 6) {
      alert('密码长度不能小于6位');
      return;
    }
    axios({
      url: 'http://localhost:9000/user/changePassword',
      method: 'GET',
      params: {
        ['userid']: userid,
        ['password']: password,
      },
      withCredentials: true,
      headers: {
        Accept: 'application/json',
        'Content-Type': 'application/json',
      },
    })
      .then((res) => {
        console.log(res);
        alert(修改成功);
      })
      .catch((err) => {
        console.log(err);
      });
  };
  return (
    <form autoComplete='false'>
      <Card>
        <CardHeader title='修改密码' />
        <Divider />
        <CardContent>
          <Grid container spacing={3}>
            <Grid item md={6} xs={12}>
              <TextField
                helperText='你可以在这里修改密码'
                label='password'
                name='password'
                onChange={(e) => {
                  setPassword(e.target.value);
                }}
                value={password}
                required
                variant='outlined'></TextField>
            </Grid>
          </Grid>
        </CardContent>
        <Divider />
        <Box>
          <Button
            sx={{
              marginLeft: '2em',
            }}
            color='primary'
            variant='outlined'
            onClick={changePassword}>
            修改密码
          </Button>
        </Box>
      </Card>
    </form>
  );
};
export default function UserInfo() {
  return (
    <div>
      <CssBaseline />
      <DashboardNavbar onSidebarOpen={false} key='navbar  ' />{' '}
      <SideBar key='sidebar' />
      <DashBoardWrapper
        sx={{
          marginLeft: '0',
          '@media(min-width: 980px)': {
            marginLeft: '300px',
          },
          zIndex: '200',
        }}>
        <Container gridTemplateColumns='auto 1fr'>
          <Typography
            sx={{
              mb: 3,
            }}
            variant='h3'>
            账户信息
          </Typography>
          <Grid container spacing={3}>
            <Grid item lg={4} md={6} xs={12}>
              <AccountProfile />
            </Grid>
            <Grid item lg={8} md={6} xs={12}>
              <EditPassword />
            </Grid>
          </Grid>
        </Container>
      </DashBoardWrapper>
    </div>
  );
}
