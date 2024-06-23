import * as React from 'react';
import AppBar from '@mui/material/AppBar';
import Box from '@mui/material/Box';
import Button from '@mui/material/Button';
import CssBaseline from '@mui/material/CssBaseline';
import Toolbar from '@mui/material/Toolbar';
import Typography from '@mui/material/Typography';
import Link from '@mui/material/Link';
import GlobalStyles from '@mui/material/GlobalStyles';
import Container from '@mui/material/Container';
import { Grid } from '@mui/material';
import Image from 'next/image';
import gif from '../public/static/gif/house.gif';
import Copyright from '../components/CopyRight';
import HouseIcon from '@mui/icons-material/House';
import styled from '@emotion/styled';
function IndexBody() {
  const title = '新一代 | 全空间';
  return (
    <Box
      sx={{
        backgroundColor: '#ffffff',
      }}>
      <GlobalStyles
        styles={{
          '*': { overflow: 'hidden' },
          ul: { margin: 0, padding: 0, listStyle: 'none' },
        }}
      />
      <CssBaseline />
      //TODO 对齐字体
      <AppBar
        position='absolute'
        color='default'
        // elevation={0}
        sx={{
          borderBottom: (theme) => `1px solid ${theme.palette.divider}`,
          paddingLeft: '10%',
          paddingRight: '10%',
        }}>
        <Toolbar sx={{ flexWrap: 'nowrap' }}>
          <HouseIcon
            fontSize='large'
            color='primary'
            sx={{ marginLeft: '2%' }}
          />
          <Typography variant='h6' color='inherit' noWrap sx={{ flexGrow: 1 }}>
            <Box
              component='span'
              sx={{
                color: 'primary.main',
              }}>
              智家
            </Box>
            {'  '} 一站式智能家居管理平台
          </Typography>
          <Button href='/login' variant='outlined' sx={{ my: 1, mx: 1.5 }}>
            登陆
          </Button>
          <nav>
            <Link
              variant='button'
              color='text.primary'
              href='/about'
              sx={{ my: 1, mx: 1.5 }}>
              关于本网站
            </Link>
          </nav>
        </Toolbar>
      </AppBar>
      <Container
        component='main'
        maxWidth='md'
        sx={{
          height: '100vh',
        }}>
        <Box
          component='div'
          sx={{
            position: 'absolute',
            top: '20vh',
            left: '15%',
            display: 'flex',
            flexDirection: 'row',
            whiteSpace: 'nowrap',
            marginBottom: '32px',
            width: '100%',
            justifyContent: 'space-between',
          }}>
          <Box
            sx={{
              marginTop: '10vh',
            }}>
            <Grid container spacing='10' color='info.main' fontSize='2em'>
              {title.split('').map((char, index) => {
                return (
                  <Grid item key={index}>
                    {char}
                  </Grid>
                );
              })}
            </Grid>
            {/* 文字部分 */}
            <Box
              sx={{
                minHeight: '2vh',
              }}></Box>
            <Box
              sx={{
                display: 'flex',
              }}>
              <Typography
                variant='h3'
                color={'text.primary'}
                sx={{
                  fontWeight: 'bold',
                }}
                noWrap>
                智能家居
              </Typography>
              <Typography variant='h3' color={'text.primary'} noWrap>
                管理平台
              </Typography>
            </Box>
            {/* 按钮 */}
            <a href='/login'>
              <Button
                variant='contained'
                component='label'
                sx={{
                  marginTop: '5vh',
                }}
                size='large'>
                现在登陆
              </Button>
            </a>
          </Box>
          {/* gif背景 */}
          <Box
            sx={{
              display: 'flex',
              alignItems: 'center',
              justifyContent: 'end',
              marginRight: '20%',
              display: 'none',
              '@media(min-width: 980px)': {
                width: '40%',
                display: 'block',
              },
            }}>
            <Image src={gif} alt='my gif' />
          </Box>
        </Box>
      </Container>
      <Container
        maxWidth='md'
        component='footer'
        sx={{
          borderTop: (theme) => `1px solid ${theme.palette.divider}`,
          mt: 8,
          py: [3, 6],
        }}>
        <Copyright sx={{ mt: 5 }} />
      </Container>
      {/* End footer */}
    </Box>
  );
}

export default function Pricing() {
  return <IndexBody />;
}
