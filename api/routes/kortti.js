const express = require('express');
const router = express.Router();
const kortti = require('../models/kortti_model');

router.get('/:id?',
 function(request, response) {
  if (request.params.id) {
    kortti.getById(request.params.id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } 
      else {
        response.json(dbResult[0]);
      }
    });
  } 
  else {
    kortti.getAll(function(err, dbResult) {
      if (err) {
        response.json(err);
      } 
      else {
        response.json(dbResult);
      }
    });
  }
});


router.post('/', 
function(request, response) {
  kortti.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
    }
  });
});


router.delete('/:id', 
function(request, response) {
  kortti.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      console.log(dbResult);
      if(dbResult.affectedRows==1){
        response.json("Kortti poistettu");
      }
      

    }
  });
});

router.put('/:id', 
function(request, response) {
  kortti.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      console.log(dbResult);
      if(dbResult.affectedRows==1){
        response.json("kortti päivitetty");
      }
      else{
        response.json("korttia ei löydy");  
      }
      
    }
  });
});

router.get('/tilinumero/:id?',
 function(request, response) {
  if (request.params.id) {
    kortti.getTilinumeroByKorttiId(request.params.id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } 
      else {
        console.log(dbResult);
        response.json(dbResult[0]);
      }
    });
  }
  });
 
router.post('/asiakasTiedot',
function(request, response) {
  kortti.asiakasTiedot
  (request.body, function(err,dbResult) {
    if (err) {
      response.json(err);
    } 
    else {
      console.log(dbResult);
      response.json(dbResult[0]);
    }
  });
});
module.exports = router;