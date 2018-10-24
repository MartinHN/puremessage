const {ClientHandler:ch} = require('./src/clients')

const c = new ch({ip:'127.0.0.1',port:'3000',protocol:'tcp'})

c.connect()