import { useEffect } from 'react';
import { DashboardNavbar } from '../components/DashNavBar';
import SideBar from '../components/DashSideBar';
import { DashBoardWrapper } from './dashboard';
import { Box } from '@mui/material';
import { useSelector } from 'react-redux';
export default function Logs() {
  const userName = useSelector((state) => state.userName.value);
  const userid = useSelector((state) => state.userID.value);

  useEffect(() => {
    console.log(userid, userName);
  }, []);
  //TODO 完成场所展示
  return (
    <div>
      <DashboardNavbar onSidebarOpen={false} key='navbar  ' />{' '}
      <SideBar key='sidebar' />
      <DashBoardWrapper>
        <Box
          sx={{
            marginLeft: '0',
            '@media(min-width: 980px)': {
              marginLeft: '300px',
            },
            zIndex: '400',
          }}></Box>
      </DashBoardWrapper>
    </div>
  );
}
