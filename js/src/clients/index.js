console.log('client')

const zmq = require('zeromq')


class ClientHandler{
  constructor(options){
    const {port,ip,protocol} = options
    this.port = port
    this.ip = ip
    this.protocol = protocol


    
  }

  connect(){
    const sock = zmq.socket('req');
    const ipStr = this.getIpStr()
    console.log('Worker connecting to '+ipStr);
    sock.connect(ipStr);
    

    sock.on('message', function(msg){
      console.log('work: %s', msg.toString());
    })
    sock.send('Hello')
    this.sock = sock
  }

  getIpStr(){
    return this.protocol+'://'+this.ip+':'+this.port
  }
}

module.exports= {
  ClientHandler
}


