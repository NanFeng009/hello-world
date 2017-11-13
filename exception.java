private void dumpStack(){
Exception e = new Exception();
StackTraceElement[] stes = e.getStackTrace();
if(null != stes){
  for(int index=0 ; index < stes.length ; index++){
    TraceDefaults.traceInterface.debug("----------------", "",stes[index].toString());
  }
}
}
