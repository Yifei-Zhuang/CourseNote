import { Box, Button, ListItem, ListItemSecondaryAction, ListItemText, TextField } from '@mui/material';
import SendIcon from '@mui/icons-material/Send';
import axios from 'axios';
import { useStorage } from '../utils/LocalStorageUtil';
import { useNavigate } from 'react-router-dom';
import { useEffect, useState } from 'react';
import LogoutIcon from '@mui/icons-material/Logout';
import { List } from '@mui/material';
import { IconButton } from '@mui/material';
import DeleteForeverIcon from '@mui/icons-material/DeleteForever';
import EditNoteIcon from '@mui/icons-material/EditNote';
import AdjustIcon from '@mui/icons-material/Adjust';
function Iteminput(props) {
    const { refresh, storage } = props;
    const navigate = useNavigate();
    const [content, setContent] = useState("");
    useEffect(() => {
        if (!storage.get("token")) {
            console.log("not login")
            navigate("/login");
        }
    }, [])
    const handleSubmit = () => {
        const data = {
            "content": content
        };
        axios.post('http://localhost:8080/todo/insert', data, {
            headers: {
                "Content-Type": "application/json",
                "Authorization": storage.get("token")
            }
        }).then(res => {
            console.log(res);
            refresh();
        }).catch(e => {
            console.log(e);
            alert(e)
        })
    };
    return (
        <>
            <TextField
                id="outlined-basic"
                label="输入任务的内容"
                variant="outlined"
                value={content}
                onChange={(e) => setContent(e.target.value)}
                sx={{
                    width: '80%'
                }}
            />
            <Button
                variant="contained"
                color="info"
                size="large"
                endIcon={<SendIcon />}
                onClick={handleSubmit}
                sx={{
                    height: '3.4rem',
                    marginLeft: '0.2rem'
                }}
            >
                添加
            </Button>
        </>
    );
}
const MyListItem = (props) => {
    const { item, refresh, storage } = props;
    const [isEditing, setIsEditing] = useState(false);
    const [newContent, setNewContent] = useState(item.content);
    const adjust = () => {
        const data = {
            "id": item.id,
            "finish": !item.finish,
            "content": item.content,
        }
        axios.post('http://localhost:8080/todo/update', data, {
            headers: {
                "Content-Type": "application/json",
                "Authorization": storage.get("token")
            }
        }).then(res => {
            console.log(res);
            refresh();
        }).catch(e => {
            console.log(e);
            alert(e)
        })
    }
    const edit = () => {
        setIsEditing(true);
    }
    const deleteTodo = () => {
        const data = {
            "id": item.id,
        }
        axios.post('http://localhost:8080/todo/delete', data, {
            headers: {
                "Content-Type": "application/json",
                "Authorization": storage.get("token")
            }
        }).then(res => {
            console.log(res);
            refresh();
        }).catch(e => {
            console.log(e);
            alert(e)
        })
    }
    const handleSubmit = () => {
        const data = {
            "id": item.id,
            "finish": item.finish,
            "content": newContent,
        }
        axios.post('http://localhost:8080/todo/update', data, {
            headers: {
                "Content-Type": "application/json",
                "Authorization": storage.get("token")
            }
        }).then(res => {
            console.log(res);
            setIsEditing(false);
            refresh();
        }).catch(e => {
            console.log(e);
            alert(e)
        })
    }
    return (isEditing ? <Box>
        <TextField
            id="outlined-basic"
            label="输入任务的内容"
            variant="outlined"
            value={newContent}
            onChange={(e) => setNewContent(e.target.value)}
            sx={{
                width: '80%'
            }}
        />
        <Button
            variant="contained"
            color="info"
            size="large"
            endIcon={<SendIcon />}
            onClick={handleSubmit}
            sx={{
                height: '3.4rem',
                marginLeft: '0.2rem'
            }}
        >
            更新
        </Button>
    </Box> :
        <>
            <ListItem>
                <ListItemText sx={{
                    textDecorationLine: item.finish ? 'line-through' : 'none'
                }}>
                    {item.content}
                </ListItemText>
                <ListItemSecondaryAction>
                    <IconButton aria-label="edit" onClick={adjust}>
                        <AdjustIcon />
                    </IconButton>
                    <IconButton aria-label="edit" onClick={edit}>
                        <EditNoteIcon />
                    </IconButton>
                    <IconButton aria-label="delete" onClick={deleteTodo}>
                        <DeleteForeverIcon />
                    </IconButton>
                </ListItemSecondaryAction>
            </ListItem >

        </>
    )
}
const DashBoard = () => {
    const itemList = [];
    const storage = useStorage();
    const navigate = useNavigate();
    let [items, setItems] = useState([]);
    useEffect(() => {
        const fetchData = async () => {
            await refresh();
        }
        fetchData();
    }, [])
    const refresh = async () => {
        console.log(refresh)
        await axios.post('http://localhost:8080/todo/all', {}, {
            headers: {
                "Content-Type": "application/json",
                "Authorization": storage.get("token")
            }
        }).then((res) => {
            console.log(res);
            setItems(res.data);
        })
    }
    const logout = () => {
        storage.clear();
        navigate("/login")
    }
    return (
        <Box sx={{
            marginTop: '2rem',
            marginLeft: '2rem'
        }}>
            <Iteminput refresh={refresh} storage={storage} />
            <Button
                variant="contained"
                color="primary"
                size="large"
                endIcon={<LogoutIcon />}
                onClick={logout}
                sx={{
                    height: '3.4rem',
                    marginLeft: '0.2rem'
                }}
            >
                退出
            </Button>
            <List>
                {
                    items.map((item) => {
                        return (
                            <MyListItem
                                key={item.id}
                                item={item}
                                refresh={refresh}
                                storage={storage}
                            />
                        );
                    })
                }
            </List>
        </Box>
    )
}
export default DashBoard;