function addListener(elem, ev, listener) {
  if(elem.addEventListener) {
    elem.addEventListener(ev, listener, false);
  } else if (elem.attachEvent) {
    elem.attachEvent('on' + ev, listener);
  } else {
    throw new Error("event listener is not supported");
  }
}

function removeListener(elem, ev, listener) {
  if(elem.removeEventListener) {
    elem.addEventListener(ev, listener, false);
  } else if (elem.detachEvent) {
    elem.detachEvent('on' + ev, listener);
  } else {
    throw new Error("event listener is not supported");
  }
}
