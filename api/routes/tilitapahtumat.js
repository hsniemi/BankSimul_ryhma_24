const express = require('express');
const router = express.Router();
const tilitapahtumat = require('../models/tilitapahtumat_model');


router.get('/:id?',
 function(request, response) {
  if (request.params.id) {
    tilitapahtumat.getById(request.params.id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult[0]);
      }
    });
  } else {
    tilitapahtumat.getAll(function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  } 
});

router.get('/getFive/:tilinumero?',
 function(request, response) {
  if (request.params.tilinumero) {
    tilitapahtumat.getFive(request.params.tilinumero, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  }
}); 

router.post('/getTen', 
function(request, response) {
  tilitapahtumat.getTen
  (request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      console.log(dbResult);
      response.json(dbResult[0]);    
    }
  });
});

router.post('/tilitapahtumat', 
function(request, response) {
  tili.tilitapahtumat(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});

router.post('/rahanNosto', 
function(request, response) {
  tilitapahtumat.rahanNosto
  (request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      console.log(dbResult);
      if(dbResult.affectedRows==1){
        response.json("Rahaa nostettu");
      }
      else if(dbResult.affectedRows==0){
        response.json("Ei tarpeeksi rahaa");
      }      
    }
  });
});

router.post('/rahanSiirto', 
function(request, response) {
  tilitapahtumat.rahanSiirto
  (request.body, function(err, dbResult) {
    if (err) {
      response.json(err.errno);
    } else {
      console.log(dbResult);
      if(dbResult.affectedRows==1){
        response.json("Rahaa siirretty");
      }
      else{
        response.json("ei tarpeeksi rahaa");
      }     
    }
  });
});
module.exports = router;



