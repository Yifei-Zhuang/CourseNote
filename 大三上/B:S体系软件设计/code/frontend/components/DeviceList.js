import {
  Button,
  Card,
  Table,
  TableBody,
  TableCell,
  TableContainer,
  TableHead,
  TablePagination,
  TableRow,
} from '@mui/material';
import { Box } from '@mui/system';
import { useState } from 'react';
import PerfectScrollbar from 'react-perfect-scrollbar';
import Router from 'next/router';
import { useDispatch } from 'react-redux';
import axios from 'axios';
import { setDeviceId } from '../redux/deviceId.slice';
export default function DeviceList(props) {
  const dispatch = useDispatch();
  const { devicelist, isDeleting, setIsDeleting, setDeviceDetailOpen } = props;
  const [limit, setLimit] = useState(10);
  const [page, setPage] = useState(0);
  const handleLimitChange = (e) => {
    setLimit(e.target.value);
  };
  const handlePageChange = (e, newPage) => {
    setPage(newPage);
  };
  //TODO 进行设备管理，比如灯开关
  const handleDeviceManage = (device) => {
    const deviceid = device.deviceId;
    dispatch(setDeviceId(deviceid));
    setDeviceDetailOpen(true);
  };
  const handleDeviceDelete = (device) => {
    const deviceid = device.deviceId;
    (async function run() {
      await axios({
        url: 'http://localhost:9000/device/delete',
        method: 'GET',
        params: {
          ['deviceId']: deviceid,
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
  return (
    <Card>
      <PerfectScrollbar>
        <Box>
          <TableContainer>
            <Table>
              <TableHead>
                <TableRow>
                  <TableCell>设备id</TableCell>
                  <TableCell>设备名</TableCell>
                  <TableCell>设备类型</TableCell>
                  <TableCell>设备描述</TableCell>
                  <TableCell>设备状态</TableCell>
                  <TableCell>管理设备</TableCell>
                  <TableCell>删除设备</TableCell>
                </TableRow>
              </TableHead>
              <TableBody>
                {devicelist.slice(0, limit).map((device, index) => {
                  let status = device.sensorValue;
                  if (device.type === 'door' || device.type === 'switch') {
                    status = device.status ? '开着' : '关闭';
                  } else if (device.type === 'light_bulb') {
                    status = `亮度：${device.brightness}`;
                  } else if (device.type === 'wet') {
                    const rand = 0;
                    status = `湿度：${device.sensorValue + rand}`;
                  } else if (device.type === 'temperature') {
                    const rand = 0;
                    status = `温度：${device.sensorValue + rand}`;
                  }
                  console.log(device);
                  return (
                    <TableRow hover key={device.deviceId}>
                      <TableCell>
                        <Box
                          sx={{
                            alignItems: 'center',
                            display: 'flex',
                          }}>
                          {index}
                        </Box>
                      </TableCell>
                      <TableCell>
                        <Box
                          sx={{
                            alignItems: 'center',
                            display: 'flex',
                          }}>
                          {device.deviceName}
                        </Box>
                      </TableCell>
                      <TableCell>
                        <Box
                          sx={{
                            alignItems: 'center',
                            display: 'flex',
                          }}>
                          {device.type}
                        </Box>
                      </TableCell>
                      <TableCell>
                        <Box
                          sx={{
                            alignItems: 'center',
                            display: 'flex',
                          }}>
                          {device.description}
                        </Box>
                      </TableCell>
                      <TableCell>
                        <Box
                          sx={{
                            alignItems: 'center',
                            display: 'flex',
                          }}>
                          {status}
                        </Box>
                      </TableCell>
                      <TableCell>
                        <Button sx={{
                          marginLeft: '-1em'
                        }} onClick={() => handleDeviceManage(device)}>
                          管理
                        </Button>
                      </TableCell>
                      <TableCell>
                        <Button sx={{
                          marginLeft: '-1em'
                        }} onClick={() => handleDeviceDelete(device)}>
                          删除
                        </Button>
                      </TableCell>
                    </TableRow>
                  );
                })}
              </TableBody>
            </Table>
          </TableContainer>
        </Box>
      </PerfectScrollbar>
      <TablePagination
        component='div'
        count={devicelist.length}
        onPageChange={handlePageChange}
        onRowsPerPageChange={handleLimitChange}
        page={page}
        rowsPerPage={limit}
        rowsPerPageOptions={[5, 10, 25]}
      />
    </Card>
  );
}
