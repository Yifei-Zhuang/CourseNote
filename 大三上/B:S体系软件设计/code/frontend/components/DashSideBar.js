import Router from 'next/router';
import Link from 'next/link';
import HouseIcon from '@mui/icons-material/House';
import OtherHousesIcon from '@mui/icons-material/OtherHouses';
import MessageIcon from '@mui/icons-material/Message';
import React from 'react';
import { ListItem, Button, Box, Divider, Drawer } from '@mui/material';
import styled from '@emotion/styled';
import LogoutIcon from '@mui/icons-material/Logout';
const SideBarBox = styled(Box)(({ theme }) => ({
  //   backgroundColor: 'theme.palette.neutral.900',
  paddingTop: '20px',
  paddingLeft: '20px',
}));
const items = [
  {
    title: '场所',
    href: '/houses',
    icon: <OtherHousesIcon fontSize='small' />,
  },
  // {
  //   title: '所有日志',
  //   href: '/logs',
  //   icon: <MessageIcon fontSize='small' />,
  // },
  // {
  //   title: '测试',
  //   href: '/test',
  //   icon: <MessageIcon fontSize='small' />,
  // },
  {
    title: '用户信息',
    href: '/UserInfo',
    icon: <MessageIcon fontSize='small' />,
  },
];
export default function SideBar(props) {
  const [open, setOpen] = React.useState(true);
  const onLogout = () => {
    setTimeout(() => {
      Router.push('/');
      console.log('change to base');
    }, 3000);
  };
  return (
    <Drawer
      anchor='left'
      open
      PaperProps={{
        sx: {
          backgroundColor: 'neutral.900',
          color: '#FFFFFF',
          width: '0',
          '@media(min-width: 980px)': {
            width: '280px',
            display: 'block',
          },
        },
      }}
      variant='permanent'>
      <SideBarBox>
        <Box
          sx={{
            display: 'flex',
            flexDirection: 'column',
          }}>
          <div>
            <Link href='/' passHref>
              <a>
                <HouseIcon
                  sx={{
                    height: 42,
                    width: 42,
                  }}
                  color='primary'
                />
              </a>
            </Link>
          </div>
        </Box>
        <Divider
          sx={{
            borderColor: '#2D3748',
            my: 3,
          }}
        />
        <Box
          sx={{
            borderColor: '#2D3748',
          }}>
          {items.map((item) => {
            return (
              <div key={item.title}>
                <ListItem
                  disableGutters
                  sx={{
                    display: 'flex',
                    mb: 0.5,
                    py: 0,
                    px: 2,
                  }}>
                  <Link href={item.href} passHref>
                    <Button
                      component='a'
                      startIcon={item.icon}
                      disableRipple
                      sx={{
                        backgroundColor: 'rgba(255,255,255, 0.08)',
                        borderRadius: 1,
                        color: 'neutral.300',
                        fontWeight: 'fontWeightBold',
                        justifyContent: 'flex-start',
                        px: 3,
                        textAlign: 'left',
                        textTransform: 'none',
                        width: '100%',
                        '& .MuiButton-startIcon': {
                          color: 'neutral.400',
                        },
                        '&:hover': {
                          backgroundColor: 'rgba(255,255,255, 0.08)',
                        },
                      }}>
                      <Box sx={{ flexGrow: 1 }}>{item.title}</Box>
                    </Button>
                  </Link>
                </ListItem>
              </div>
            );
          })}
          <div key={'logout'}>
            <ListItem
              disableGutters
              sx={{
                display: 'flex',
                mb: 0.5,
                py: 0,
                px: 2,
              }}>
              <Button
                component='a'
                startIcon={<LogoutIcon fontSize='small' />}
                disableRipple
                sx={{
                  backgroundColor: 'rgba(255,255,255, 0.08)',
                  borderRadius: 1,
                  color: 'neutral.300',
                  fontWeight: 'fontWeightBold',
                  justifyContent: 'flex-start',
                  px: 3,
                  textAlign: 'left',
                  textTransform: 'none',
                  width: '100%',
                  '& .MuiButton-startIcon': {
                    color: 'neutral.400',
                  },
                  '&:hover': {
                    backgroundColor: 'rgba(255,255,255, 0.08)',
                  },
                }}>
                <Box sx={{ flexGrow: 1 }} onClick={onLogout}>
                  退出账户
                </Box>
              </Button>
            </ListItem>
          </div>
          <Divider sx={{ borderColor: '#2D3748' }} />
        </Box>
      </SideBarBox>
    </Drawer>
  );
}
