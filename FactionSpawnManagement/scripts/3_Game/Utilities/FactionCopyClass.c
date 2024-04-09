class FactionCopyClass<Class T>
{
    static void Copy(T dataIn, out T dataOut)
    {
        string data = JsonFileLoader<T>.JsonMakeData(dataIn);
        JsonFileLoader<T>.JsonLoadData(data, dataOut);
    }
}