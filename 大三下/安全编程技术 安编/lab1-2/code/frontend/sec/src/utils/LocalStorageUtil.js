const useStorage = () => {
    const save = (key, data) => {
        window.localStorage.setItem(key, JSON.stringify((data)));
    };
    const get = (key) => {
        const localData = window.localStorage.getItem(key);
        if (localData && localData !== "") {
            return JSON.parse(localData);
        } else {
            return false;
        }
    };
    /**
     * 清除 localStorage 中 valKey 的值
     */
    const clear = (key) => {
        window.localStorage.setItem(key, "");
    };
    return {
        save,
        get,
        clear,
    };
};
// 清除所有的 localStorage
const cleanAll = () => {
    window.localStorage.clear();
};
export {
    useStorage,
    cleanAll
}
