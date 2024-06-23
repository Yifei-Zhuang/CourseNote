import { useRef, useState } from 'react';
import React from 'react';
import styled from '@emotion/styled';
import { AppBar, Avatar, Box, Toolbar } from '@mui/material';
import AccountCircleIcon from '@mui/icons-material/AccountCircle';
import { AccountPopover } from './account';
import theme from './theme';
const DashboardNavbarRoot = styled(AppBar)(({ theme }) => ({
  backgroundColor: theme.palette.background.paper,
  boxShadow: theme.shadows[3],
}));

export const DashboardNavbar = (props) => {
  const { onSidebarOpen, ...other } = props;
  const accountref = useRef(null);
  const [openAccountPopover, setOpenAccountPopover] = useState(false);

  return (
    <>
      <DashboardNavbarRoot
        sx={{
          left: {
            lg: 280,
          },
          position: 'relative',
          width: {
            lg: '100vw',
            '@media(min-width: 980px)': {
              width: 'calc(100vw - 280px)',
              display: 'block',
            },
          },
        }}>
        <Toolbar
          disableGutters
          sx={{
            minHeight: 64,
            left: 0,
            px: 2,
          }}>
          <Box sx={{ flexGrow: 1 }} />

          <Avatar
            onClick={() => {
              setOpenAccountPopover(true);
              // setAnchorel(accountref.current);
            }}
            ref={accountref}
            sx={{
              cursor: 'pointer',
              height: 40,
              width: 40,
              ml: 1,
              backgroundColor: 'black',
            }}>
            <AccountCircleIcon fontSize='small' />
          </Avatar>
          <AccountPopover
            open={openAccountPopover}
            onClose={() => {
              setOpenAccountPopover(false);
            }}
            anchorEl={accountref.current}
          />
        </Toolbar>
      </DashboardNavbarRoot>
    </>
  );
};
