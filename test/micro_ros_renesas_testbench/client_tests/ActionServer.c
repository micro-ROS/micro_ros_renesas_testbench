#include "./utils.h"
#include "config.h"

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <example_interfaces/action/fibonacci.h>

void microros_app(void);
void fibonacci_worker();
rcl_ret_t handle_goal(rclc_action_goal_handle_t * goal_handle, void * context);
bool handle_cancel(rclc_action_goal_handle_t * goal_handle, void * context);

#define MAX_GOAL 20

rclc_executor_t executor;
rclc_action_goal_handle_t * goal_ptr;
bool goal_received = false;

void fibonacci_worker()
{
    rcl_action_goal_state_t goal_state;

    int32_t response_data[MAX_GOAL] = {};
    uint32_t response_index = 0;

    example_interfaces__action__Fibonacci_SendGoal_Request * req = (example_interfaces__action__Fibonacci_SendGoal_Request *) goal_ptr->ros_goal_request;
    example_interfaces__action__Fibonacci_GetResult_Response response = {0};

    if (req->goal.order > MAX_GOAL)
    {
        goal_state = GOAL_STATE_ABORTED;
    }
    else
    {
        response_data[0] = 0;
        response_data[1] = 1;
        response_index = 2;

        for (size_t i = 2; i < (size_t) req->goal.order && !goal_ptr->goal_cancelled; i++)
        {
            response_data[i] = response_data[i - 1] + response_data[i - 2];
            response_index++;
            sleep_ms(10);
        }

        if (!goal_ptr->goal_cancelled)
        {
            response.result.sequence.data = &response_data[0];
            response.result.sequence.capacity = (size_t) req->goal.order;
            response.result.sequence.size = response_index;
            goal_state = GOAL_STATE_SUCCEEDED;
        }
        else
        {
            goal_state = GOAL_STATE_CANCELED;
        }
    }

    rcl_ret_t rc;
    do
    {
        rc = rclc_action_send_result(goal_ptr, goal_state, &response);

        if (rc != RCL_RET_OK)
        {
            // Spin to get goal request
            rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
        }
    } while (rc != RCL_RET_OK);
}

rcl_ret_t handle_goal(rclc_action_goal_handle_t * goal_handle, void * context)
{
    (void) context;

    example_interfaces__action__Fibonacci_SendGoal_Request * req =
        (example_interfaces__action__Fibonacci_SendGoal_Request *) goal_handle->ros_goal_request;

    // Too big, rejecting
    if (req->goal.order > MAX_GOAL) {
        return RCL_RET_ACTION_GOAL_REJECTED;
    }

    goal_ptr = goal_handle;
    goal_received = true;
    return RCL_RET_ACTION_GOAL_ACCEPTED;
}

bool handle_cancel(rclc_action_goal_handle_t * goal_handle, void * context)
{
    (void) context;
    (void) goal_handle;

    return true;
}

void microros_app(void)
{
    rcl_allocator_t allocator = rcl_get_default_allocator();

    //create init_options
    rclc_support_t support;

    rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
    rcl_init_options_init(&init_options, allocator);
    rcl_init_options_set_domain_id(&init_options, DOMAIN_ID);
    rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator);

    // create node
    rcl_node_t node;
    rclc_node_init_default(&node, "test_node", "", &support);

    // Create action service
    rclc_action_server_t action_server;
	rclc_action_server_init_default(
        &action_server,
        &node,
        &support,
        ROSIDL_GET_ACTION_TYPE_SUPPORT(example_interfaces, Fibonacci),
        "test_fibonacci");

    // Create executor
    rclc_executor_init(&executor, &support.context, 1, &allocator);

    example_interfaces__action__Fibonacci_SendGoal_Request ros_goal_request[1];
    rclc_executor_add_action_server(
        &executor,
        &action_server,
        1,
        ros_goal_request,
        sizeof(example_interfaces__action__Fibonacci_SendGoal_Request),
        handle_goal,
        handle_cancel,
        (void *) &action_server);

    while (true)
    {
    	if (goal_received)
        {
    		fibonacci_worker();
			goal_ptr = NULL;
			goal_received = false;
    	}

        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
        sleep_ms(10);
    }
}
