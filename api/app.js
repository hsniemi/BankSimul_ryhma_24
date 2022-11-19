var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var asiakasRouter = require('./routes/asiakas');
var korttiRouter = require('./routes/kortti');
var tiliRouter = require('./routes/tili');
var tilitapahtumatRouter = require('./routes/tilitapahtumat');
var kirjautuminenRouter = require('./routes/kirjautuminen');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/asiakas', asiakasRouter);
app.use('/kortti', korttiRouter);
app.use('/tili', tiliRouter);
app.use('/tilitapahtumat', tilitapahtumatRouter);
app.use('/kirjautuminen', kirjautuminenRouter);

module.exports = app;
