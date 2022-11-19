const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const kirjautuminen = require('../models/kirjautuminen_model');

router.post('/', 
  function(request, response) {
    if(request.body.id && request.body.pinkoodi){
      const id = request.body.id;
      const pinkoodi = request.body.pinkoodi;
        kirjautuminen.tarkistaPinkoodi(id, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError);
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(pinkoodi,dbResult[0].pinkoodi, function(err,compareResult) {
                if(compareResult) {
                  console.log("succes");
                  response.send(true);
                }
                else {
                    console.log("väärä pinkoodi");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("korttia ei löydy");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("kortinnumero tai pinkoodi puuttuu");
      response.send(false);
    }
  }
);

module.exports=router;