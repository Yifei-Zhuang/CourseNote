import {
  Button,
  Card,
  Table,
  TableBody,
  TableCell,
  TableHead,
  TablePagination,
  TableRow,
} from '@mui/material';
import { Box } from '@mui/system';
import { useState } from 'react';
import PerfectScrollbar from 'react-perfect-scrollbar';
import Router from 'next/router';
import { useDispatch } from 'react-redux';
import { setRoom as higherSetRoom } from '../redux/room.slice';
import axios from 'axios';
export default function RoomList(props) {
  //   const rooms = [
  //     {
  //       roomid: '1',
  //       name: 'bedroom',
  //       description: 'my bedroom',
  //     },
  //   ];
  const dispatch = useDispatch();
  const { rooms, isDeleting, setIsDeleting } = props;
  const [limit, setLimit] = useState(10);
  const [page, setPage] = useState(0);
  const setRoom = (roomid) => {
    dispatch(higherSetRoom(roomid));
  };
  const handleLimitChange = (e) => {
    setLimit(e.target.value);
  };
  const handlePageChange = (e, newPage) => {
    setPage(newPage);
  };
  const handleRoomDelete = (room) => {
    const roomid = room.roomId;
    (async function run() {
      console.log('in axios');
      await axios({
        url: 'http://localhost:9000/room/delete',
        method: 'GET',
        params: {
          ['roomid']: roomid,
        },
        withCredentials: true,
        headers: {
          Accept: 'application/json',
          'Content-Type': 'application/json',
        },
      })
        .then((res) => {
          setIsDeleting(!isDeleting);
        })
        .catch((error) => {
          console.log(error);
        });
    })();
  };
  const handleRoomMange = (room) => {
    // TODO 完成页面跳转逻辑，跳转到指定的room

    setRoom(room.roomId);
    Router.push('/room');
  };
  return (
    <Card>
      <PerfectScrollbar>
        <Box sx={{ minWidth: 1050 }}>
          <Table>
            <TableHead>
              <TableRow>
                <TableCell>RoomID</TableCell>
                <TableCell>名称</TableCell>
                <TableCell>介绍</TableCell>
                <TableCell>管理</TableCell>
                <TableCell>删除 </TableCell>
              </TableRow>
            </TableHead>
            <TableBody>
              {rooms.slice(0, limit).map((room, index) => {
                return (
                  <TableRow hover key={room.roomId}>
                    <TableCell>
                      <Box
                        sx={{
                          alignItems: 'center',
                          display: 'flex',
                        }}>
                        {index + 1}
                      </Box>
                    </TableCell>
                    <TableCell>
                      <Box
                        sx={{
                          alignItems: 'center',
                          display: 'flex',
                        }}>
                        {room.name}
                      </Box>
                    </TableCell>
                    <TableCell>
                      <Box
                        sx={{
                          alignItems: 'center',
                          display: 'flex',
                        }}>
                        {room.description}
                      </Box>
                    </TableCell>
                    <TableCell>
                      <Button sx={{
                        marginLeft: '-1em'
                      }} onClick={() => handleRoomMange(room)}>
                        管理
                      </Button>
                    </TableCell>
                    <TableCell>
                      <Button sx={{
                        marginLeft: '-1em'
                      }} onClick={() => handleRoomDelete(room)}>
                        删除
                      </Button>
                    </TableCell>
                  </TableRow>
                );
              })}
            </TableBody>
          </Table>
        </Box>
      </PerfectScrollbar>
      <TablePagination
        component='div'
        count={rooms.length}
        onPageChange={handlePageChange}
        onRowsPerPageChange={handleLimitChange}
        page={page}
        rowsPerPage={limit}
        rowsPerPageOptions={[5, 10, 25]}
      />
    </Card>
  );
}
