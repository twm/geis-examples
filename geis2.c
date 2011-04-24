#include <errno.h>
#include <geis/geis.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>

void
dump_errors(Geis geis, GeisString where)
{
  GeisSize count = geis_error_count(geis);
  if (count)
  {
    printf("%d errors for %s:\n", count, where);
  }
  for (GeisSize i = 0; i < count; i++)
  {
    GeisStatus status = geis_error_code(geis, i);
    GeisString msg = geis_error_message(geis, i);
    printf("%u: %4d \"%s\"\n", i, status, msg);
  }
}

int
main(int argc, char* argv[])
{
  GeisStatus status = GEIS_STATUS_SUCCESS;
  Geis geis;
  GeisSubscription subscription;
  GeisFilter filter;
  int        fd;

  geis = geis_new(GEIS_INIT_UTOUCH_XCB, NULL);
  dump_errors(NULL, "new geis");

  subscription = geis_subscription_new(geis, "example", GEIS_SUBSCRIPTION_CONT);
  dump_errors(geis, "new subscription");

  filter = geis_filter_new(geis, "filter");
  dump_errors(geis, "new filter");

  status = geis_filter_add_term(filter,
                       GEIS_FILTER_DEVICE,
                       GEIS_DEVICE_ATTRIBUTE_DIRECT_TOUCH, GEIS_FILTER_OP_EQ, GEIS_TRUE,
                       NULL);
  dump_errors(geis, "add filter term: direct touch");

  status = geis_subscription_add_filter(subscription, filter);
  dump_errors(geis, "add filter");

  status = geis_subscription_activate(subscription);
  dump_errors(geis, "subscription activate");

  geis_subscription_delete(subscription);
  geis_delete(geis);
}

// vim: set ts=2, et
