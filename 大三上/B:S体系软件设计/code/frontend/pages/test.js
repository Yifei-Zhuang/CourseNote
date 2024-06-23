import axios from 'axios';
import { useEffect, useState } from 'react';
import { useSelector } from 'react-redux';

export default function testPage() {
  const [isLoading, setIsLoading] = useState(true);
  const [image, setImage] = useState(null);
  let roomid = useSelector((state) => state.room.value);
  const mySetImage = (image) => {
    return new Promise((resolve, reject) => {
      setImage(image);
      resolve();
    });
  };
  axios({
    method: 'GET',
    url: 'http://localhost:9000/image/get',
    params: {
      ['roomid']: roomid,
    },
    withCredentials: true,
    headers: {
      Accept: 'application/json',
      'Content-Type': 'application/json',
    },
  }).then(async (res) => {
    const result = res.data;
    if (!result.status) {
      console.log('error', res);
    } else {
      mySetImage(result.image);
    }
  });
  useEffect(() => {
    setIsLoading(false);
  }, [image]);
  // 进行图片渲染测试
  return (
    <div>
      {isLoading ? (
        <h1>Loading</h1>
      ) : (
        <img src={`data:image/png;base64,${image}`} />
      )}
    </div>
  );
}
