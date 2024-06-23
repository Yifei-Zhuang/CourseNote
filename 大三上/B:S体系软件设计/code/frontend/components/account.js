import Router from 'next/router';
import React from 'react';
import { Box, MenuItem, MenuList, Popover, Typography } from '@mui/material';
import { setUserName as higherSetUserName } from '../redux/username.slice';
import { setUserID as highersetUserID } from '../redux/userid.slice';
import { useDispatch, useSelector } from 'react-redux';

export const AccountPopover = (props) => {
  const dispatch = useDispatch();
  const { anchorEl, open, onClose } = props;
  const userName = useSelector((state) => state.userName.value);
  const mySetUserName = (username) => {
    dispatch(higherSetUserName(username));
  };
  const mySetUserId = (userid) => {
    dispatch(highersetUserID(userid));
  };
  const handleSignOut = () => {
    mySetUserName('');
    mySetUserId(-1);
    Router.push('/');
  };
  return (
    <Popover
      anchorEl={anchorEl}
      sx={{
        position: 'absolute',
        right: 0,
        top: '50px',
        zIndex: '50',
      }}
      anchorOrigin={{
        vertical: 'bottom',
        horizontal: 'right',
      }}
      transformOrigin={{
        vertical: 'top',
        horizontal: 'right',
      }}
      onClose={onClose}
      open={open}
      PaperProps={{
        sx: { width: '300px' },
      }}>
      <Box
        sx={{
          py: 1.5,
          px: 2,
        }}>
        <Typography variant='body1'>用户名</Typography>
        <Typography color='text.secondary' variant='body2'>
          {userName}
        </Typography>
      </Box>
      <MenuList
        disablePadding
        sx={{
          '& > *': {
            '&:first-of-type': {
              borderTopColor: 'divider',
              borderTopStyle: 'solid',
              borderTopWidth: '1px',
            },
            padding: '12px 16px',
          },
        }}>
        <MenuItem onClick={handleSignOut}>登出</MenuItem>
      </MenuList>
    </Popover>
  );
};
