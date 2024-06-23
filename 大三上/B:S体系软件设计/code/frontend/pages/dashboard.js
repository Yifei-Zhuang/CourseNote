import { useEffect } from 'react';
import React from 'react';
import { DashboardNavbar } from '../components/DashNavBar';
import { AccountPopover } from '../components/account';
import { useState } from 'react';
import { styled, Typography } from '@mui/material';
import SideBar from '../components/DashSideBar';
import { useSelector } from 'react-redux';
export const DashBoardWrapper = styled('div')(({ theme }) => ({
  display: 'flex',
  flex: '1 1 auto',
  maxWidth: '100%',
  paddingTop: 64,
}));
export default function dashboard() {
  const userName = useSelector((state) => state.userName.value);
  const userid = useSelector((state) => state.userID.value);
  useEffect(() => {
    console.log(userid, userName);
  }, []);
  return (
    <div>
      <DashboardNavbar onSidebarOpen={false} key='navbar  ' />{' '}
      <SideBar key='sidebar' />
      <DashBoardWrapper>
        <Typography
          sx={{
            marginLeft: '0',
            '@media(min-width: 980px)': {
              marginLeft: '300px',
            },
            zIndex: '200',
          }}
          variant='h1'>
          欢迎使用智能家居管理网站
        </Typography>
      </DashBoardWrapper>
    </div>
  );
}
